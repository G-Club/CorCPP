#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include "model/userinfo.pb.h"
#include "include/socketclientex.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc<3)
    {
        std::cout<<"input addr&port"<<std::endl;
        return 0;
    }
    std::string ip;
    ip=argv[1];
    int port,ret;

    port=atoi(argv[2]);
    std::cout<<"hello world"<<std::endl;
    SEX_ERR_TYPE err=SEX_ERROR;
    SocketClientEx client;
    client.setAddress(ip);
    client.setPort(port);
    ret=client.Init();
    if(ret !=0)
    {
        std::cout<<"socket init failed\n";
        return 0;
    }
    err=client.Connect(3);
    if(err==SEX_TIME_OUT)
    {
        std::cout<<"connect to server time out"<<std::endl;
        return 0;
    }
    std::string msg("yes it is");
    client.Send(msg,3);

    client.DisConnect();

    return 0;
}
