
#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <iostream>
#include <string>

#ifdef WIN32

#include <WS2tcpip.h>
#include <winsock2.h>

typedef SOCKET SOCKETex_t;

#define SEX_INVALID_SOCKET INVALID_SOCKET
#define ioctl ioctlsocket
#define Errcode GetLastError()
#define close closesocket
#define S_PROTO_TCP IPPROTO_TCP
#define SEX_EINPROGRESS  WSAEWOULDBLOCK

#endif

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

enum SEX_ERR_TYPE
{
	SEX_NONE_ERR=0,
	SEX_TIME_OUT = 1,
	SEX_ERROR=2
};
class SocketClientEx
{
public:
	SocketClientEx();

	int Init();
	/*
	*连接方法，带超时时间
	*/
	SEX_ERR_TYPE Connect2(std::string &ip, unsigned short port, unsigned int timeout);
	
	~SocketClientEx();

private:
	SOCKETex_t handle;
	fd_set fs;

protected:

};

