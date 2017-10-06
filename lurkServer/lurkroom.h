#ifndef LURKROOM_H
#define LURKROOM_H
#include "LURK.h"
#include "LURKer.h"
using namespace LURK;
class LurkRoom
{
public:
    roomPkg room;
    std::vector<roomPkg> connections;
    std::map<std::string,LURKer*> players;
    std::vector<charPkg> respawner;
    std::vector<charPkg> monsters;
    std::map<std::string,charPkg> dead;
    LurkRoom();
    LurkRoom & fight();
    LurkRoom & fightPvp(std::string initiater,std::string target);
    LurkRoom & update();
    LurkRoom & loot(std::string looter, std::string target);
    LurkRoom & respawn();
    LurkRoom & removeChar(std::string name);
    LurkRoom & addChar(LURKer &name);
};
#endif // LURKROOM_H
