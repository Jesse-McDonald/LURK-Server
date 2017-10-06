#ifndef LURKWORLD_H
#define LURKWORLD_H
#include "LURK.h"
#include "lurkroom.h"

#include "LURKer.h"
class LurkWorld
{
public:
    __uint16_t start_room;
    LurkWorld();
    std::map<std::string,LURKer*> players;
    std::vector<LurkRoom> rooms;
    gamePkg game;

    LurkWorld& message(msgPkg message);
    LurkWorld& join(LURKer& player);
    LurkWorld& leave(std::string name);
    LurkWorld& intro(LURKer &player);
    LurkWorld& changeRoom(int num,LURKer &player);
    LurkWorld& begin(LURKer &player);



};

#endif // LURKWORLD_H
