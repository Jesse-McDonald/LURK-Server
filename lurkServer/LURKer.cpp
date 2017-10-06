#include "LURKer.h"
#include <pthread.h>
#include "LURKing.h"
#include <iostream>
LURKer::LURKer(int fd)
{
    client_fd=fd;

}
LURKer::LURKer(){

}
LURKer& LURKer::spin(){
     this->closeThread=false;
     pthread_create(&(myThread),NULL, LURKer::reader,(void*)this);
     return *this;
}
void* LURKer::reader(void* param){
    LURKer* self=(LURKer*) param;
    while(!(self->closeThread)){
       self->receive();
       self->handle();
    }
    return param;
}


LURKer& LURKer::stop(){
    this->closeThread=true;
    pthread_join((this->myThread),0);
    return *this;
}
LURKer& LURKer::receive(){//change to return LURK* and set class level pkg *currentPack

    unsigned char type;
    pkg* ret;
    try{
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        ////std::cout<<"startning read loop"<<std::endl;

        read(this->client_fd,&type,1);

        ////std::cout<<"type recieved: "<<(int)type<<std::endl;
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        switch (type){
        case 1:{//done
            //std::cout<<"Reading Message"<<std::endl;
            msgPkg *temp=new msgPkg();
            temp->type=type;
            unsigned short len;
            //std::cout<<"Reading len"<<std::endl;
            read(this->client_fd,&(len),2);
            //std::cout<<"len is: "<<len <<std::endl;
            //std::cout<<"Reading rec name"<<std::endl;
            read(this->client_fd,&(temp->recName),32);
            //std::cout<<"rec name is: "<<temp->recName <<std::endl;
            //std::cout<<"Reading sender"<<std::endl;
            read(this->client_fd,&(temp->sender),32);
            for(int i=0;i<32;i++){temp->sender[i]=currentChar.name[i];}
            //std::cout<<"sender is: "<<temp->sender <<std::endl;
            //std::cout<<"Reading message"<<std::endl;
            char * descBuffer = new char[len+1];
            read(this->client_fd,descBuffer,len);
            //std::cout<<"message is: "<<descBuffer <<std::endl;
            temp->msg = std::string(descBuffer, len);
            delete[] descBuffer;
            ret=temp;
            }break;
        case 2:{//change room
            changeRoomPkg *temp=new changeRoomPkg();
            temp->type=type;
            read(this->client_fd,&(temp->room),2);
            ret=temp;
        }break;
        case 4:{//pvp fight
            pvpPkg *temp=new pvpPkg;
            temp->type=type;
            read(this->client_fd,&(temp->target),32);
            ret=temp;
        }break;
        case 5:{//loot
            lootPkg *temp=new lootPkg;
            temp->type=type;
            read(this->client_fd,&(temp->target),32);
            ret=temp;
        }break;
        case 10:{//done
            //std::cout<<"Reading character"<<std::endl;
            charPkg *temp=new charPkg();
            temp->type=type;
            //std::cout<<"Reading name"<<std::endl;
            read(this->client_fd,&(temp->name),32);
            //std::cout<<"name is: "<<temp->name<<std::endl;
            //std::cout<<"reading flags"<<std::endl;
            char b;
            read(this->client_fd,&b,1);
            temp->flags=std::bitset<8>(b);
            //std::cout<<"flags are: "<<temp->flags<<std::endl;
            //std::cout<<"Reading atk"<<std::endl;
            read(this->client_fd,&(temp->atk),2);
            //std::cout<<"atk is: "<<temp->atk<<std::endl;
            //std::cout<<"Reading def"<<std::endl;
            read(this->client_fd,&(temp->def),2);
            //std::cout<<"Def is: "<<temp->def<<std::endl;
            //std::cout<<"Reading Reg"<<std::endl;
            read(this->client_fd,&(temp->reg),2);
            //std::cout<<"Reg is: "<<temp->reg<<std::endl;
            //std::cout<<"Reading health"<<std::endl;
            read(this->client_fd,&(temp->health),2);
            //std::cout<<"health is: "<<temp->health<<std::endl;
            //std::cout<<"Reading gold"<<std::endl;
            read(this->client_fd,&(temp->gold),2);
            //std::cout<<"gold is"<<temp->gold<<std::endl;
            //std::cout<<"Reading room"<<std::endl;
            read(this->client_fd,&(temp->room),2);
            //std::cout<<"room is: "<<temp->room<<std::endl;
            //std::cout<<"Reading len"<<std::endl;
            unsigned short len;
            read(this->client_fd,&len,2);
            //std::cout<<"len is: "<<len<<std::endl;
            char * descBuffer = new char[len+1];
            //std::cout<<"Reading description"<<std::endl;
            read(this->client_fd,descBuffer,len);
            temp->description = std::string(descBuffer, len);
            //std::cout<<"Description is: "<<descBuffer<<std::endl;
            delete[] descBuffer;

            ret=temp;
        }break;
        default:{//done, leave, fight, and start all use this
            ret=new pkg();
            ret->type=type;

            }
        }
    }catch(...){
        ret=new pkg();
        ret->type=12;
    };
    //pthread_mutex_lock(&(this->readLock));
    //if(this->cPak!=&(this->nulPak)){
    //    delete cPak;
    //    cPak=&nulPak;
    //}
    //pthread_mutex_unlock(&(this->readLock));
    this->lock();
    this->cPak.reset(ret);
    this->pks.push(cPak);
    this->unlock();
    return *this;
}
LURKer& LURKer::lock(){
    pthread_mutex_lock(&(this->readLock));
    return *this;
}
LURKer& LURKer::unlock(){
    pthread_mutex_unlock(&(this->readLock));
    return *this;
}
LURKer& LURKer::sendRoom(roomPkg room){
    write(client_fd,&(room.type),1);
    write(client_fd,&(room.number),2);
    write(client_fd,&room.name,32);
    int len=room.description.length();
    write(client_fd, &len, 2);
    write(client_fd,(room.description.c_str()),len);
    return *this;
}
LURKer& LURKer::sendChar(charPkg chr){
    int skt=client_fd;
    //chr.type=10;
    write(skt, &(chr.type), 1);
    //std::cout<<(int)chr.type;
    write(skt, &(chr.name), 32);
    char d=(char)chr.flags.to_ulong();
    //void * f=(void *)&inPak.flags;
    //char *d=(char*)f;
    //write(skt,&(inPak.flags),1);
    write(skt, &d,1);

    write(skt, &(chr.atk),2);
    write(skt, &(chr.def),2);
    write(skt, &(chr.reg),2);
    write(skt, &(chr.health),2);
    write(skt, &(chr.gold),2);
    write(skt, &(chr.room),2);
    int len=chr.description.length();
    write(skt, &len, 2);
    write(skt, (chr.description.c_str()),len);
    return *this;
}
LURKer& LURKer::sendGame(gamePkg game){
    write(client_fd,(void*)&game.type,1);
    write(client_fd,(void*)&game.init,2);
    write(client_fd,(void*)&game.statMax,2);
    int len=game.description.length();
    write(client_fd, &len, 2);
    write(client_fd, (game.description.c_str()),len);
//    //std::cout<<(int)game.type<<std::endl;
//    //std::cout<<(int)game.init<<std::endl;
//    //std::cout<<(int)game.statMax<<std::endl;
//    //std::cout<<game.description<<std::endl;


    return *this;

}
LURKer& LURKer::sendMsg(msgPkg msg){
    write(client_fd,&(msg.type),1);
    __uint16_t len=msg.msg.length();
    write(client_fd, &len, 2);
    write(client_fd,&msg.recName,32);
    write(client_fd,&msg.sender,32);
    write(client_fd, (msg.msg.c_str()),len);
    return *this;
}
LURKer& LURKer::sendError(errorPkg error){
    write(client_fd,&(error.type),1);
    write(client_fd,&(error.code),1);
    int len=error.msg.length();
    write(client_fd, &len, 2);
    write(client_fd, (error.msg.c_str()),len);
    return *this;
}

LURKer& LURKer::sendAccept(__uint8_t type2){
    char c=8;
    write(client_fd,&c,1);
    write(client_fd,&type2,1);
    return *this;
}
LURKer& LURKer::sendStart(){
    char c=6;
    write(client_fd,&c,1);
    return *this;
}
void LURKer::sever(){
    char c=12;
    write(client_fd,&c,1);\
    this->closeThread=true;
    close(client_fd);
}
#include "lurkworld.h"
LURKer& LURKer::handle(){
    while(!pks.empty()){
        pkg* current=(pks.front().get());
        std::cout<<(int)current->type<<std::endl;

        if(current->type== 1){
            if(ready){
            msgPkg working=*((msgPkg*) current);
            lurk.world.message(working);
            }else{
             errorPkg error;
             error.msg="Not yet ready to do this";
             error.type=7;
             error.code=5;
              sendError(error);
            }

        }else
        if(current->type== 2){
            if(ready){
            changeRoomPkg working=*((changeRoomPkg*) current);
            lurk.world.changeRoom(working.room,*this);
            }else{
             errorPkg error;
             error.msg="Not yet ready to do this";
             error.type=7;
             error.code=5;
              sendError(error);
            }

        }else
        if(current->type== 3){
            if(ready){
                lurk.world.rooms[currentChar.room].fight();
            }else{
             errorPkg error;
             error.msg="Not yet ready to do this";
             error.type=7;
             error.code=5;
              sendError(error);
            }

        }else
        if(current->type== 4){
            if(ready){
                pvpPkg working=*((pvpPkg*) current);
                lurk.world.rooms[currentChar.room].fightPvp(currentChar.name,working.target);

            }else{
             errorPkg error;
             error.msg="Not yet ready to do this";
             error.type=7;
             error.code=5;
              sendError(error);
            }


        }else
        if(current->type== 5){
            if(ready){
                lootPkg working=*((lootPkg*) current);
                lurk.world.rooms[currentChar.room].loot(currentChar.name,working.target);
            }else{
             errorPkg error;
             error.msg="Not yet ready to do this";
             error.type=7;
             error.code=5;
             sendError(error);
            }
        }else
        if(current->type== 6){
            if(charPrimed){
                std::cout<<"its the worlds fault";
                lurk.world.begin(*this);
                ready=true;
            }else{
             errorPkg error;
             error.msg="Not yet ready to do this";
             error.type=7;
             error.code=5;
             sendError(error);
            }
        }else
        if(current->type== 10){
            if(!ready){
                lurk.world.join(*this);
            }else{
                std::cout<<"wrong path\n";
                sendChar(currentChar);
            }
        }else
        if(current->type== 12){

            lurk.world.leave(currentChar.name);
            closeThread=true;
            lurk.leave(*this);
        }
        pks.pop();

    return *this;
    }
}
