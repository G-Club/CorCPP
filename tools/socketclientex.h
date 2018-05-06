#ifndef SOCKETCLIENTEX_H
#define SOCKETCLIENTEX_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __linux
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <sys/ioctl.h>

#define INVALID_SOCKET -1
#define Errcode errno
#define close close

#define S_PROTO_TCP 0
#define SEX_EINPROGRESS  EINPROGRESS

#endif

#define _in_
#define _out_
#define _in_out_

class SocketClientEx
{
public:

    enum SEX_ERR_TYPE
    {
        SEX_NONE_ERR=0,
        SEX_TIME_OUT = 1,
        SEX_ERROR=2,
        SEX_NONE_CONNECT=3
    };

public:
    SocketClientEx();

    int InitializeBySocket(int fd);
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
    int Receive(_out_ std::string *msg, unsigned int timeout);
    /*
    *接收信息
    */
    int Receive(_out_ char* msg, unsigned int len, unsigned int timeout);
    /*
    *发送信息
    */
    int Send(_in_ std::string &msg, unsigned int timeout);
    /*
    *发送信息
    */
    int Send(const char* msg, unsigned int len, unsigned int timeout);
    /*
    *獲取對端的地址
    */
    std::string GetPeerAddress();
    /*
    *獲取對端的端口
    */
    uint16_t GetPeerPort();
    /*
    *獲取本地鏈接使用的端口
    */
    uint16_t GetConnPort();

    ~SocketClientEx();

private:
    void getuseport();
    void Reset();
    int Init();

protected:
    std::string address;
    uint16_t peerport;
    uint16_t clientport;
    int handle;
    fd_set fdset;
    bool isconnected;


};


#endif // SOCKETCLIENTEX_H
