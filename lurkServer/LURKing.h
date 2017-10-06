#ifndef LURKING_H
#define LURKING_H
#include "LURK.h"
#include "LURKer.h"
#include "lurkworld.h"
class LURKer;

using namespace LURK;

class LURKing
{
private:
    struct sockaddr_in sad;
    int skt = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in cad;
    socklen_t cad_size;
    pthread_mutex_t readLock = PTHREAD_MUTEX_INITIALIZER;
public:
    std::vector<LURKer> players;
    LURKing();
    LURKing& establish(int port);
    LURKing& accept();
    std::queue<std::shared_ptr<pkg>> gPks;
    LURKing& lock();
    LURKing& unlock();
    LurkWorld world;
    LURKing& leave(LURKer& player);

};
extern LURKing lurk;
#endif // LURKER_H
