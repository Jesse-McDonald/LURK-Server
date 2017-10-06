#ifndef LURK_H
#define LURK_H
#include <vector>
#include "LURK.h"
#include <bitset>
#include <queue>
#include <memory>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdint>
#include <string>
#include <memory>
#include <map>

class LURKer;
class LURKing;
class LurkWorld;
class LurkRoom;
namespace LURK{
    struct pkg{
        pkg(){type=0;}
         __uint8_t type;
    virtual ~pkg(){}
    };

    struct charPkg:public pkg{

      char name[32]={0};
      std::bitset<8> flags;
      __uint16_t atk;
      __uint16_t def;
      __uint16_t reg;
      signed short health;
      __uint16_t gold;
      __uint16_t room;
      std::string description;
      inline charPkg(__int16_t t,char n[32],__uint8_t f, __uint16_t a, __uint16_t d, __uint16_t r, signed short h, __uint16_t g, std::string desc){type=t;for(int i=0;i<32;i++)name[i]=n[i];flags=f;atk=a;def=d;reg=r;health=h;gold=g;description=desc;}
      inline charPkg(){}
      charPkg(const charPkg &chr){
          this->type=chr.type;
          this->atk=chr.atk;
          this->def=chr.def;
          this->description=chr.description;
          this->flags=chr.flags;
          this->gold=chr.gold;
          this->health=chr.health;
          for (int i=0;i<32;i++){
              this->name[i]=chr.name[i];
          }
          this->reg=chr.reg;
          this->room=chr.room;
      }
    };
    struct msgPkg:public pkg{

        char recName[32];
        char sender[32];
        std::string msg;
    };

    struct pvpPkg:public pkg{
        char target[32];
    };
    struct lootPkg:public pkg{
        char target[32];
    };
    struct changeRoomPkg:public pkg{
        __uint16_t room;
    };
    struct fightPkg:public pkg{};
    struct errorPkg:public pkg{
        __uint8_t code;
        std::string msg;

    };
    struct roomPkg:public pkg{
        roomPkg(){}
        roomPkg(const roomPkg &room){
            this->description=room.description;
            this->type=room.type;
            this->number=room.number;
            for (int i=0;i<32;i++){
                this->name[i]=room.name[i];
            }
        }
        __uint16_t number;
        char name[32];
        std::string description;
    };
    struct gamePkg:public pkg{
        __uint16_t init;
        __uint16_t statMax;
        std::string description="UNDEF";
};
}
#endif // LURK_H

