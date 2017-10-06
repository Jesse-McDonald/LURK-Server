#include "server.h"
#include "LURK.h"
#include "LURKer.h"
#include "LURKing.h"
#include "cstring"
LURKing lurk=LURKing();

int master(int port){
        LurkRoom room=LurkRoom();
        roomPkg connection;
        charPkg chr;
        lurk.world.game.description="This is just a very simple game";
        lurk.world.game.init=100;
        lurk.world.game.statMax=999;
        lurk.world.game.type=11;

        chr.flags[8]=1;
        chr.flags[7]=1;
        chr.flags[6]=1;
        chr.type=10;
        lurk.world.start_room=1;
//        room.room.type=9;
//        room.room.number=0;
//        memcpy(room.room.name,"DEV room",32);
//        room.room.description="You should NEVER see this room";
//        room.connections.push_back(connection);
        {
                room.room.type=9;
                room.room.number=1;
                memcpy(room.room.name,"Starting room",32);
                room.room.description="This is the starting room";

                connection.description="just the next room, nothing to see in there";
                memcpy(connection.name,"The Next room",32);
                connection.number=2;
                connection.type=13;

                room.connections.push_back(connection);
        }
        lurk.world.rooms.push_back(room);
        room.connections.clear();
        room.monsters.clear();

        {
                room.room.type=9;
                room.room.number=2;
                memcpy(room.room.name,"Room 2",32);
                room.room.description="This is the second room, dont question it";

                connection.description="this is the starting room, dont go back there";
                memcpy(connection.name,"Starting room",32);
                connection.number=1;
                connection.type=13;

                room.connections.push_back(connection);

                connection.description="Just some weak monsters, they are easy to kill";
                memcpy(connection.name,"Grinding room",32);
                connection.number=3;

                room.connections.push_back(connection);

                connection.description="some shops in here, maybe";
                memcpy(connection.name,"Shop room",32);
                connection.number=4;

                room.connections.push_back(connection);

                connection.description="the \"quest\" starts in here";
                memcpy(connection.name,"Quest room",32);
                connection.number=5;

                room.connections.push_back(connection);
        }
                lurk.world.rooms.push_back(room);
                room.connections.clear();
                room.monsters.clear();

        {
            room.room.type=9;
            room.room.number=3;
            memcpy(room.room.name,"Grinding room",32);
            room.room.description="This is a room for grinding monster, but there is no real point so jokes on you :)";

            connection.description="just the next room, nothing to see in there";
            memcpy(connection.name,"The Next room",32);
            connection.number=2;

            room.connections.push_back(connection);

            chr.atk=0;

            chr.def=0;
            chr.description="This monster has no attack or deffense, just kill it already";
            chr.gold=10;
            chr.health=10;
            chr.reg=1;
            chr.room=3;
            chr.gold=10;
            memcpy(chr.name,"Punching bag 1",32);

            room.monsters.push_back(chr);
            chr.def=10;
            chr.description="This monster has some deffense, just kill it already";
            chr.gold=10;
            chr.health=10;
            chr.reg=1;
            chr.room=3;
            chr.gold=10;
            memcpy(chr.name,"Punching bag 2",32);
            room.monsters.push_back(chr);


            chr.def=20;
            chr.description="This monster has some deffense, just kill it already";
            chr.gold=10;
            chr.health=10;
            chr.reg=1;
            chr.room=3;
            chr.gold=10;
            memcpy(chr.name,"Punching bag 3",32);
            room.monsters.push_back(chr);

            chr.def=30;
            chr.description="This monster has some deffense, just kill it already";
            chr.gold=10;
            chr.health=10;
            chr.reg=1;
            chr.room=3;
            chr.gold=10;
            memcpy(chr.name,"Punching bag 4",32);
            room.monsters.push_back(chr);


            chr.def=40;
            chr.description="This monster has some deffense";
            chr.gold=10;
            chr.health=10;
            chr.reg=1;
            chr.room=3;
            chr.gold=10;
            memcpy(chr.name,"Punching bag 5",32);
            room.monsters.push_back(chr);


            chr.def=50;
            chr.description="This monster has much deffense";
            chr.gold=10;
            chr.health=10;
            chr.reg=1;
            chr.room=3;
            chr.gold=10;
            memcpy(chr.name,"Punching bag 6",32);
            room.monsters.push_back(chr);


            chr.def=60;
            chr.description="This monster has much deffense";
            chr.gold=10;
            chr.health=10;
            chr.reg=1;
            chr.room=3;
            chr.gold=10;
            memcpy(chr.name,"Punching bag 7",32);
            room.monsters.push_back(chr);


            chr.def=70;
            chr.description="This monster has much deffense";
            chr.gold=10;
            chr.health=10;
            chr.reg=1;
            chr.room=3;
            chr.gold=10;
            memcpy(chr.name,"Punching bag 8",32);
            room.monsters.push_back(chr);


            chr.def=80;
            chr.description="This monster has much deffense";
            chr.gold=10;
            chr.health=10;
            chr.reg=1;
            chr.room=3;
            chr.gold=10;
            memcpy(chr.name,"Punching bag 9",32);
            room.monsters.push_back(chr);

        }
                        lurk.world.rooms.push_back(room);
                        room.connections.clear();
                        room.monsters.clear();

        {
            room.room.type=9;
            room.room.number=4;
            memcpy(room.room.name,"Shoping room",32);
            room.room.description="This is a room for shoping, but there are no shops so bummer for you";
            room.connections.push_back(connection);
            connection.description="just the next room, nothing to see in there";
            memcpy(connection.name,"The Next room",32);
            connection.number=2;

            room.connections.push_back(connection);
        }
                                lurk.world.rooms.push_back(room);
                                room.connections.clear();
                                room.monsters.clear();

        {
            room.room.type=9;
            room.room.number=5;
            memcpy(room.room.name,"Quest room",32);
            room.room.description="The quest starts here, your quest, make it to the end of this line and kill the boss";

            connection.description="just the last room, nothing to see in there";
            memcpy(connection.name,"The last room",32);
            connection.number=2;
            room.connections.push_back(connection);
            connection.description="the next room in the quest";
            memcpy(connection.name,"The Next room",32);
            connection.number=6;

            room.connections.push_back(connection);
        }
                                        lurk.world.rooms.push_back(room);
                                        room.connections.clear();
                                        room.monsters.clear();

        {
            room.room.type=9;
            room.room.number=6;
            memcpy(room.room.name,"Quest 2 room",32);
            room.room.description="The brave hero has started his quest";

            connection.description="just the last room, nothing to see in there";
            memcpy(connection.name,"The last room",32);
            connection.number=5;
            room.connections.push_back(connection);
            connection.description="the next room in the quest";
            memcpy(connection.name,"The Next room",32);
            connection.number=7;

            room.connections.push_back(connection);
        }
            lurk.world.rooms.push_back(room);
            room.connections.clear();
            room.monsters.clear();

        {
            room.room.type=9;
            room.room.number=7;
            memcpy(room.room.name,"Quest 3 room",32);
            room.room.description="as our hero aproches the bend she notices something";

            connection.description="just the last room, nothing to see in there";
            memcpy(connection.name,"The last room",32);
            connection.number=6;
            room.connections.push_back(connection);
            connection.description="the next room in the quest";
            memcpy(connection.name,"The Next room",32);
            connection.number=8;

            room.connections.push_back(connection);
        }
            lurk.world.rooms.push_back(room);
            room.connections.clear();
            room.monsters.clear();

        {
            room.room.type=9;
            room.room.number=8;
            memcpy(room.room.name,"Quest 4 room",32);
            room.room.description="nvm, it was nothing";

            connection.description="just the last room, nothing to see in there";
            memcpy(connection.name,"The last room",32);
            connection.number=7;
            room.connections.push_back(connection);
            connection.description="the next room in the quest";
            memcpy(connection.name,"The Next room",32);
            connection.number=9;

            room.connections.push_back(connection);
        }
            lurk.world.rooms.push_back(room);
            room.connections.clear();
            room.monsters.clear();

        {
            room.room.type=9;
            room.room.number=9;
            memcpy(room.room.name,"Quest 5 room",32);
            room.room.description="almost there";

            connection.description="just the last room, nothing to see in there";
            memcpy(connection.name,"The last room",32);
            connection.number=8;
            room.connections.push_back(connection);
            connection.description="the next room in the quest";
            memcpy(connection.name,"The Next room",32);
            connection.number=10;

            room.connections.push_back(connection);
        }
            lurk.world.rooms.push_back(room);
            room.connections.clear();
            room.monsters.clear();

        {
            room.room.type=9;
            room.room.number=10;
            memcpy(room.room.name,"Quest Boss room",32);
            room.room.description="now you must defeat the boss";

            connection.description="just the last room, nothing to see in there";
            memcpy(connection.name,"The last room",32);
            connection.number=9;


            room.connections.push_back(connection);
            room.monsters.push_back(chr);
            chr.def=90;
            chr.description="This monster is the boss, be cairful";
            chr.gold=1000;
            chr.health=1000;
            chr.reg=10;
            chr.room=10;
            chr.atk=100;
            memcpy(chr.name,"Not a punching bag",32);
            room.monsters.push_back(chr);

        }
            lurk.world.rooms.push_back(room);
            room.connections.clear();
            room.monsters.clear();

        lurk.establish(port);
        while(true){
            lurk.accept();
        }
}
