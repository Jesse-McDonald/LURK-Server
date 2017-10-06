#include "lurkroom.h"
#include "lurkworld.h"
#include "algorithm"
#include "jalib.h"
LurkRoom::LurkRoom()
{

}
struct sortPlayer{
bool operator()(LURKer *a, LURKer *b){return a->currentChar.def<b->currentChar.def;}
};
struct sortMonster{
bool operator()(charPkg a, charPkg b){return a.atk<b.atk;}};
LurkRoom& LurkRoom::fight(){
    std::vector<LURKer*> playerList;
    int playerR=0;
    int monsterR=0;
    if(players.empty()||monsters.empty()){
        return *this;
    }
    for(auto it = players.cbegin(); it != players.cend(); ++it)
    {
    if(it->second->currentChar.flags[7]==1){
        LURKer* player=(LURKer*)&(it->second);
        playerList.push_back(player);}
    }
    std::sort(playerList.begin(),playerList.end(),sortPlayer());
    std::sort(monsters.begin(),monsters.end(),sortMonster());
    for(int i=0;i<playerList.size();i++){
        playerR+=playerList[i]->currentChar.reg;
        if(monsters.size()>0){
            monsters[0].health-= jalib::min(0,playerList[i]->currentChar.atk-monsters[0].def);
            if (monsters[0].health<=0){
                monsters[0].flags[8]=0;
                dead.insert(std::pair<std::string,charPkg>(monsters[0].name,monsters[0]));
                monsters.erase(monsters.begin());

            }
        }
    }
    for(int i=0;i<monsters.size();i++){
        monsterR+=monsters[i].reg;
        if(playerList.size()>0){
            playerList[0]->currentChar.health-= jalib::min(0,monsters[i].atk-playerList[0]->currentChar.def);
            if (playerList[0]->currentChar.health<=0){
                playerR-=playerList[0]->currentChar.reg;
                playerList[0]->currentChar.flags[8]=0;
                dead.insert(std::pair<std::string,charPkg>(playerList[0]->currentChar.name,playerList[0]->currentChar));
                playerList[0]->ready=false;
                players.erase(playerList[0]->currentChar.name);
                playerList.erase(playerList.begin());

            }
        }
    }
    for(int i=0;i<playerList.size();i++){
        int needed=playerList[i]->currentChar.reg*10+playerList[i]->currentChar.def*10-playerList[i]->currentChar.health;
        int used=jalib::min(needed,playerR);
        playerR-=used;
        playerList[i]->currentChar.health+=used;
    }
    for(int i=0;i<monsters.size();i++){
        int needed=monsters[i].reg*10+monsters[i].def*10-monsters[i].health;
        int used=jalib::min(needed,monsterR);
        playerR-=used;
        monsters[i].health+=used;
    }
    update();
    return *this;
}

LurkRoom& LurkRoom::fightPvp(std::string aggressor,std::string target){
    if(players.empty()){
        return *this;
    }
    if(players[target]->currentChar.flags[7]==1){
    players[aggressor]->currentChar.health=jalib::min(players[target]->currentChar.atk-players[aggressor]->currentChar.def,0);
    players[target]->currentChar.health=jalib::min(players[aggressor]->currentChar.atk-players[target]->currentChar.def,0);
    if(players[aggressor]->currentChar.health<=0){

        players[aggressor]->currentChar.flags[8]=0;
        dead.insert(std::pair<std::string,charPkg>(aggressor,players[aggressor]->currentChar));
        players[aggressor]->ready=false;
        players.erase(aggressor);

    }else{
     players[aggressor]->currentChar.health+=players[aggressor]->currentChar.reg;
     players[aggressor]->currentChar.health=jalib::min((int)players[aggressor]->currentChar.health,players[aggressor]->currentChar.def*10+players[aggressor]->currentChar.reg*10);
    }
    if(players[target]->currentChar.health<=0){

        players[target]->currentChar.flags[8]=0;
        dead.insert(std::pair<std::string,charPkg>(target,players[target]->currentChar));
        players[target]->ready=false;
        players.erase(target);

    }else{
     players[target]->currentChar.health+=players[target]->currentChar.reg;
     players[target]->currentChar.health=jalib::min((int)players[target]->currentChar.health,players[target]->currentChar.def*10+players[target]->currentChar.reg*10);
    }
    update();
    }else{
        errorPkg error=errorPkg();
        error.code=7;
        error.msg="Player name "+target+" does not accept fights.";
        error.type=7;
        players[aggressor]->sendError(error);
    }
    return *this;

}
LurkRoom& LurkRoom::update(){
    for(auto it = players.cbegin(); it != players.cend(); ++it)
    {

        LURKer *t=it->second;
        t->sendRoom(room);
        for(auto it = players.cbegin(); it != players.cend(); ++it){
            t->sendChar(it->second->currentChar);
        }
        for(int i=0;i<monsters.size();i++){
            t->sendChar(monsters[i]);
        }
        for(int i=0;i<connections.size();i++){
            t->sendRoom(connections[i]);
        }
        for(auto it = dead.cbegin(); it != dead.cend(); ++it)
        {
            t->sendChar(it->second);
        }
    }
    return *this;
}
LurkRoom& LurkRoom::loot(std::string looter, std::string target){
    players[looter]->currentChar.gold+=dead[target].gold;
    dead.erase(target);
    update();
    return *this;
}
LurkRoom& LurkRoom::respawn(){
    monsters=respawner;
    return *this;
}
LurkRoom& LurkRoom::removeChar(std::string name){
        players.erase(name);
}
LurkRoom& LurkRoom::addChar(LURKer &player){
    players.insert(std::pair<std::string,LURKer*>(player.currentChar.name,&player));
    update();
}
