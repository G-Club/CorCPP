#include "include/socketservice.h"
#include <arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<netinet/tcp.h>
#include<sys/types.h>

SocketService::SocketService():ismd5(false)
{

}

SocketService::~SocketService()
{

}

int SocketService::Init()
{
    fd=socket(PF_INET,SOCK_STREAM,0);
    if(fd<0)
    {
        std::cout<<"socket init error"<<std::endl;
        return -1;
    }
    if(ismd5)
    {
        setMd5Signature();
    }

}

void SocketService::SetTcpMd5(bool isuse)
{
    this->ismd5=isuse;
}

std::string SocketService::getAddr() const
{
    return addr;
}

void SocketService::setAddr(const std::string &value)
{
    addr = value;
}

uint16_t SocketService::getPort() const
{
    return port;
}

void SocketService::setPort(const uint16_t &value)
{
    port = value;
}

int SocketService::getFd() const
{
    return fd;
}

int SocketService::setMd5Signature()
{
    int ret=0;
    ret=setsockopt(fd,IPPROTO_TCP,TCP_MD5SIG,&md5sig,TCP_MD5SIG_MAXKEYLEN);
    return ret;
}

std::string SocketService::getMd5Pwd() const
{
    return md5_pwd;
}

void SocketService::setMd5Pwd(const std::string &value)
{
    md5_pwd = value;
}
