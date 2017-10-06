#include "lurkworld.h"
#include <cstring>
#include<iostream>
LurkWorld::LurkWorld()
{

}
LurkWorld& LurkWorld::message(msgPkg message){
    if(players.find(message.recName)!=players.end()){
        players[message.recName]->sendMsg(message);
    }else{
        errorPkg error=errorPkg();
        error.code=6;
        error.msg="Player "+(std::string)message.recName+" could not be found.";
        error.type=7;
        msgPkg msg=msgPkg();

        strcpy("[SERVER]",msg.sender);
        for(int i=0;i<32;i++){msg.recName[i]=message.sender[i];}
        msg.type=1;
        msg.msg=error.msg;
        players[message.sender]->sendError(error);
        players[message.sender]->sendMsg(msg);

    }
}
LurkWorld& LurkWorld::join(LURKer& player){
    charPkg currentChar=*((charPkg*)player.pks.front().get());
    int total=currentChar.atk+currentChar.def+currentChar.reg;
    if(players.find(currentChar.name)!=players.end()){
        errorPkg error=errorPkg();
        error.code=2;
        error.msg="Player name "+(std::string)currentChar.name+" is already taken.";
        error.type=7;
        player.sendError(error);
    }else if(total>game.init){
        std::cout<<game.init<<" "<<total;
        errorPkg error=errorPkg();
        error.code=4;
        error.msg="Not enough points for stats";
        error.type=7;
        player.sendError(error);
    }else if(total>game.statMax){

        errorPkg error=errorPkg();
        error.code=2;
        error.msg="Stats excede game limit";
        error.type=7;
        player.sendError(error);
    }else{
        currentChar.flags[8]=1;
        currentChar.flags[6]=0;
        currentChar.flags[5]=1;
        currentChar.flags[4]=0;
        currentChar.gold=0;
        currentChar.health=currentChar.def*10+currentChar.reg*10;
        player.sendChar(currentChar);
        player.charPrimed=true;
        players.insert(std::pair<std::string,LURKer*>(player.currentChar.name,&player));
        player.currentChar=currentChar;

    }
}
LurkWorld& LurkWorld::begin(LURKer &player){
            player.currentChar.flags[4]=1;
            player.currentChar.room=start_room;
            player.sendChar(player.currentChar);

            rooms[start_room-1].addChar(player);
}
LurkWorld& LurkWorld::leave(std::string name){
    rooms[players[name]->currentChar.room].players.erase(name);
    players.erase(name);
}
LurkWorld& LurkWorld::intro(LURKer& player){
    player.sendGame(this->game);
    std::cout<<"sent game package";
}
LurkWorld& LurkWorld::changeRoom(int num,LURKer &player){
    bool good=false;
    for(int i=0;i<rooms[player.currentChar.room-1].connections.size();i++){

        if ((rooms[player.currentChar.room-1].connections[i].number)==num){
            good=true;
            break;
        }
    }
    if(good){
        rooms[player.currentChar.room-1].removeChar(player.currentChar.name);
        player.currentChar.room=num;
        rooms[num-1].addChar(player);
    }else{
     errorPkg error;
     error.code=7;
     error.msg="No connection";
     error.code=1;
     player.sendError(error);
    }
}
