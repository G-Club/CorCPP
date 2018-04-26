#include "epserver.h"
#include <fcntl.h>
#include "loghelper.h"

EPServer::EPServer():port(0),epfd(0),isstop(false)
{

}

EPServer::EPServer(const EPServer &&serv)
{

}

EPServer::~EPServer()
{

}

EPServer& EPServer::operator=(const EPServer &serv)
{
    return *this;
}

void EPServer::SetPort(uint16_t port)
{
    this->port =port;
}

uint16_t EPServer::GetPort()
{
    return this->port;
}

void EPServer::Set_CB_OnConnect(CB_OnConnect cb_onconn)
{
    this->cb_onconnect=cb_onconn;
}

void EPServer::Set_CB_Oneadable(CB_OnReadable cb_onread)
{
    this->cb_onreadable=cb_onread;
}

void EPServer::SetEpollListen(int fd, int events, void *data)
{
    EpollAdd(fd,events,data);
}

void EPServer::DelEpollListen(int fd)
{
    EpollDelete(fd);
}

int EPServer::Initialization()
{
    InitSocket();

    InitEpoll();

    return 0;
}

int EPServer::Run()
{
    struct epoll_event events[max_event]={0};
    std::cout<<"Start Listen port:"<<this->port<<" .....\n"<<std::endl;

    while (!isstop)
    {
        int count= epoll_wait(this->epfd,events,max_event,INFINITY_WAIT);
        OnEvent(events,count);
    }
    Clean();
    return 0;
}

int EPServer::Stop()
{
    isstop=true;
    return 0;
}

void EPServer::Clean()
{
    DataMap::iterator iter;

    for(iter=this->datamap.begin();iter != this->datamap.end();++iter)
    {
        close(iter->first);
        if(NULL !=iter->second)
        {
            SocketDoc *pdoc=reinterpret_cast<SocketDoc*>(iter->second);
            delete pdoc;
        }
    }
    close(this->lsfd);
}

int EPServer::InitEpoll()
{
    this->epfd=epoll_create(1024);
    bzero(&this->event,sizeof(this->event));
    this->event.events=EPOLLIN;
    this->event.data.fd=this->lsfd;
    epoll_ctl(this->epfd,EPOLL_CTL_ADD,this->lsfd,&event);
    return 0;
}

void EPServer::OnEvent(struct epoll_event *r_events,int count)
{
    if(r_events==NULL)
    {
        return;
    }
    struct epoll_event cur_event;
    int i=0;
    for(i=0;i<count;++i)
    {
        cur_event=r_events[i];

        if(cur_event.events & EPOLLIN && cur_event.data.fd==lsfd)
        {
            OnConnect();
        }
        else if(cur_event.events & EPOLLIN )
        {
            OnReadable(cur_event.data.ptr);
        }
    }
}

int EPServer::SetNonBlock(int fd)
{
    int flag=0,ret=0;
    flag=fcntl(fd,F_GETFL);

    flag|=O_NONBLOCK;
    ret= fcntl(fd,F_SETFL,flag);//设置非阻塞
    return ret;
}

void EPServer::EpollAdd(int fd, int events, void *data)
{
    struct epoll_event event;
    bzero(&event,sizeof(event));
    // event.data.fd=fd;
    event.events=events;

    SocketDoc *pdoc=new SocketDoc;
    pdoc->data=data;
    pdoc->fd=fd;

    event.data.ptr=pdoc;

    epoll_ctl(this->epfd,EPOLL_CTL_ADD,fd,&event);
    std::pair<int,void*> pr(fd,reinterpret_cast<void*>(pdoc));
    //datamap.insert(pr);
    //C++11新添加的方法 函数在容器中直接构造元素 好像能快点
    datamap.emplace(std::pair<int,void*>(fd,reinterpret_cast<void*>(pdoc)));
}

void EPServer::EpollDelete(int fd)
{
    epoll_ctl(this->epfd,EPOLL_CTL_DEL,fd,NULL);

    void *doc=datamap[fd];
    if(NULL==doc)
    {
        return ;
    }
    SocketDoc *pdoc=reinterpret_cast<SocketDoc*>(doc);
    if(NULL !=pdoc)
    {
        delete pdoc ;
        pdoc=nullptr;
    }

}

void EPServer::OnConnect()
{
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    socklen_t len=sizeof(client);
    int cfd= accept(this->lsfd,(struct sockaddr*)&client,&len);
    if(cfd<1)
    {
        return ;
    }

    if(this->cb_onconnect ==NULL)
    {
        return;
    }
    //设置非阻塞
    SetNonBlock(cfd);
    this->cb_onconnect(*this,cfd,(struct sockaddr*)&client);

}

void EPServer::OnReadable(void *arg)
{
    SocketDoc *pdoc=reinterpret_cast<SocketDoc*>(arg);
    if(NULL ==pdoc)
    {
        return;
    }
    if(NULL !=this->cb_onreadable)
    {
        this->cb_onreadable(*this,pdoc->fd,pdoc->data);
    }

}

void EPServer::OnWriteable(void *arg)
{
    SocketDoc *pdoc=reinterpret_cast<SocketDoc*>(arg);
    if(NULL !=pdoc)
    {
        delete pdoc;
        pdoc=nullptr;
    }
    if(this->cb_onwriteable !=NULL)
    {
      this->cb_onwriteable(*this,pdoc->fd,pdoc->data);
    }

}

//初始化socket
int EPServer::InitSocket()
{
    int flag=1;
    this->lsfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in local;
    bzero(&local,sizeof(local));
    local.sin_addr.s_addr=INADDR_ANY;
    local.sin_family=AF_INET;
    local.sin_port=htons(this->port);
    //设置地址复用
    setsockopt(this->lsfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));

    bind(this->lsfd,(struct sockaddr*)&local,sizeof(local));
    listen(this->lsfd,SOMAXCONN);

    return 0;
}
