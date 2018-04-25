#ifndef EPSERVER_H
#define EPSERVER_H

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/select.h>
#include <unistd.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>
#include <map>

#define _in_ //输入参数
#define _out_ //输出参数
#define _in_out_  //输入输出参数

#define INFINITY_WAIT -1 //无限等待

class EPServer
{
public:
    typedef void (*CB_OnConnect)(EPServer &server,int cfd,struct sockaddr *client);
    typedef void (*CB_OnReadabel)(EPServer &server,int cfd,void *arg);
    typedef void (*CB_OnWriteabel)(EPServer &server,int cfd,void *arg);
    typedef
    struct _socketdata
    {
        int fd;
        void *data;
    } SocketDoc;

    typedef std::map<int,void*> DataMap;

public:
    EPServer();
    ~EPServer();

    int Initialization();

    int Run();
    int Stop();
    void SetPort(uint16_t port);
    void Set_CB_OnConnect(CB_OnConnect cb_onconn);
    void Set_CB_Oneadabel(CB_OnReadabel cb_onread);
    void SetEpollListen(int fd, int events, void *data);
    void DelEpollListen(int fd);
    uint16_t GetPort();

private:
    int lsfd;
    bool isstop;
    uint16_t port;
    int epfd;
    const unsigned int max_event=20;
    struct epoll_event event;
    CB_OnConnect cb_onconnect;
    CB_OnReadabel cb_onreadabel;
    CB_OnReadabel cb_onwriteabel;
    DataMap datamap;

private:
    void OnEvent(struct epoll_event *r_events,int count);
    int InitSocket();
    int InitEpoll();

    int SetNonBlock(int fd);

    void EpollAdd(int fd, int events, void *data);

    void EpollDelete(int fd);

    void OnConnect();

    void OnReadable(void *arg);

    void OnWriteable(void *arg);

    void Clean();
   // void CloseAll();
    //不让拷贝 不让移动 不让赋值
    EPServer(const EPServer &serv);
    EPServer(const EPServer &&serv);
    EPServer& operator=(const EPServer &serv);
};

#endif // EPSERVER_H
