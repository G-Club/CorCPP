
#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <iostream>
#include <string>
#ifdef linux
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>

typedef int SOCKETex_t;

#define SEX_INVALID_SOCKET -1
#define Errcode errno
#define close close

#define S_PROTO_TCP 0
#define SEX_EINPROGRESS  EINPROGRESS

#endif



class SocketClientEx
{

public:
    enum SEX_ERR_TYPE
    {
        SEX_NONE_ERR=0,
        SEX_TIME_OUT = 1,
        SEX_ERROR=2
    };

    SocketClientEx();

    int Init();
    /*
    *连接方法，带超时时间
    */
    SEX_ERR_TYPE Connect2(std::string &ip, unsigned short port, unsigned int timeout);
    /*
    *断开连接
    */
    SEX_ERR_TYPE DisConnect();
    /*
    *接收信息
    */
    int Receive(std::string &msg, unsigned int timeout);
    /*
    *接收信息
    */
    int Receive(char* msg, unsigned int len, unsigned int timeout);
    /*
    *发送信息
    */
    int Send(std::string &msg, unsigned int timeout);
    /*
    *发送信息
    */
    int Send(const char* msg, unsigned int len, unsigned int timeout);

    ~SocketClientEx();

private:
    SOCKETex_t handle;
    fd_set fs;
    bool isconnected;
    void SetBlock(bool b);

protected:

};

