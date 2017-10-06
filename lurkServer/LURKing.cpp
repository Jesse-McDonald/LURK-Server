#include "LURKing.h"
#include <iostream>
#include <signal.h>
LURKing::LURKing(){}
LURKing& LURKing::establish(int port){
    sad.sin_port=htons(port);
    sad.sin_addr.s_addr = INADDR_ANY;
    sad.sin_family = AF_INET;\
    bind(skt, (struct sockaddr *)(&sad), sizeof(struct sockaddr_in));
    listen(skt, 5);
}
LURKing& LURKing::accept(){
    int fd=::accept(skt,(struct sockaddr *)(&cad), &cad_size);

    players.push_back(LURKer(fd));
    players.back().id=players.size()-1;
        std::cout<<"Accepted player\n";
    world.intro(players.back());

    players.back().charPrimed=false;
    players.back().ready=false;
    signal(SIGPIPE, SIG_IGN);
    //I wish signal(SIGFAULT, SIG_IGN);
    try{
        players.back().spin();
    }catch(...){};


}
LURKing& LURKing::lock(){
    pthread_mutex_lock(&(this->readLock));
    return *this;
}
LURKing& LURKing::unlock(){
    pthread_mutex_unlock(&(this->readLock));
    return *this;
}
LURKing& LURKing::leave(LURKer& player){
    players.erase(players.erase(players.begin()+player.id));
    world.leave(player.currentChar.name);
}
