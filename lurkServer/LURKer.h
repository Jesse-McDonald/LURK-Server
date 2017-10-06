#ifndef LURKER_H
#define LURKER_H
#include "LURK.h"

using namespace LURK;
class LURKer
{
private:

    int client_fd;
    pthread_t myThread;
    bool closeThread=false;

    static void* reader(void* param);
    LURKer& receive();
    LURKer& handle();
    pthread_mutex_t readLock = PTHREAD_MUTEX_INITIALIZER;
public:
    int id;
    bool ready;
        LURKer& spin();
    charPkg currentChar;
    LURKer& stop();
    LURKer& lock();
    LURKer& sendRoom(roomPkg);
    LURKer& sendChar(charPkg);
    LURKer& sendGame(gamePkg);
    LURKer& sendMsg(msgPkg);
    LURKer& sendError(errorPkg);
    LURKer& sendAccept(__uint8_t);
    LURKer& sendStart();
    LURKer& unlock();
    void sever();
    LURKer();
    LURKer(int fd);
    std::shared_ptr<pkg> cPak;
    std::queue<std::shared_ptr<pkg>> pks;
    bool charPrimed;
};
#endif // LURKER_H
