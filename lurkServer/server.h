#ifndef SERVER_H
#define SERVER_H
#include<string>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/ip.h>
#include<unistd.h>
using namespace std;
int master(int port);


#endif // SERVER_H
