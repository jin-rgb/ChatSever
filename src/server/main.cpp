#include"chatserver.hpp"
#include"chatservice.hpp"
#include <signal.h>
#include <iostream>
using namespace std;

//处理服务器ctrl+c后，重置用户登录信息
void resHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cerr << "command invalid! example ./ChatClient 127.0.0.1 6000" << endl;
        exit(-1);
    }
    signal(SIGINT,resHandler);

    char *ip=argv[1];
    uint16_t port = atoi(argv[2]);

    EventLoop loop;
    InetAddress addr(ip,port);
    ChatServer server(&loop,addr,"ChatServer");

    server.start();
    loop.loop();
    return 0;
}