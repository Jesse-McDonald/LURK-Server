#include <iostream>
#include "jalib.h"
#include "server.h"
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{

    cout << "Hello World!" << endl;
    master(atoi(argv[1]));
    cout<<"Goodbye World!"<<endl;
    return 0;
}
