#include "socketclientex.h"

SocketClientEx::SocketClientEx() :peerport(0),clientport(0),isconnected(false)
{

    handle = INVALID_SOCKET;
}

int SocketClientEx::Init()
{
    this->handle = socket(AF_INET, SOCK_STREAM, S_PROTO_TCP);
    if (INVALID_SOCKET == this->handle)
    {
        std::cout << "create socket error" << std::endl;
        return -1;
    }

    return 0;
}

SocketClientEx::SEX_ERR_TYPE  SocketClientEx::Connect2(std::string &ip, unsigned short port, unsigned int timeout)
{
    if(INVALID_SOCKET == handle)
    {
        Init();
    }
    if (INVALID_SOCKET == handle)
    {
        return SEX_ERR_TYPE::SEX_ERROR;
    }
    if(ip.empty() || port<1)
    {
        return  SEX_ERR_TYPE::SEX_ERROR;
    }
    int ret;
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serv.sin_addr);

    SEX_ERR_TYPE errc = SEX_ERR_TYPE::SEX_NONE_ERR;

    unsigned long ul = 1;

    do
    {
        ioctl(handle, FIONBIO, &ul); //设置为非阻塞模式
        ret = connect(handle, (struct sockaddr*)&serv, sizeof(serv));
        int ecode = Errcode;

        if (ret == -1 && ecode == EINPROGRESS)
        {
            struct timeval timer;
            timer.tv_sec = timeout;
            timer.tv_usec = 0;

            FD_ZERO(&fdset);
            FD_SET(handle, &fdset);
            /*
            select会阻塞直到检测到事件或则超时，如果超时，select会返回0，
            如果检测到事件会返回1，如果异常会返回-1，如果是由于信号中断引起的异常errno==EINTR
            */
            ret = select(handle + 1, NULL, &fdset, NULL, &timer);
            if (ret == 0)
            {
                errc = SEX_ERR_TYPE::SEX_TIME_OUT;
                Reset();
                break;
            }

            if (FD_ISSET(handle, &fdset))
            {
                socklen_t len = sizeof(ret);
                ecode = getsockopt(handle, SOL_SOCKET, SO_ERROR, &ret, &len);
                /* 如果发生错误，Solaris实现的getsockopt返回-1，
                   * 把pending error设置给errno. Berkeley实现的
                   * getsockopt返回0, pending error返回给error.
                   * 我们需要处理这两种情况 */
                if (ecode < 0 || ret)
                {
                    Reset();
                    break;
                }
            }

            isconnected = true;

            getuseport();

            this->address=ip;
            this->peerport=port;

        }
        else if (ret == -1)
        {
            errc = SEX_ERR_TYPE::SEX_ERROR;
            Reset();
            break;
        }

    } while (0);

    ul = 0;
    ioctl(handle, FIONBIO, &ul); //设置阻塞模式

    return errc;
}

/*
*接收信息
*返回接收到的字节数
*/
int SocketClientEx::Receive(_out_ std::string *msg, unsigned int timeout)
{
    if (!isconnected || handle == INVALID_SOCKET)
    {
        return 0;
    }
    char buff[1024] = { 0 };
    int count = 0;
    FD_ZERO(&fdset);
    FD_SET(handle, &fdset);

    unsigned long ul = 1;
    ioctl(handle, FIONBIO, &ul); //设置为非阻塞模式

    while (1)
    {
        memset(buff, 0, sizeof(buff));
        int c = 0;
        c = Receive(buff, sizeof(buff), timeout);
        if (c > 0)
        {
            msg->append(buff, c);
            count += c;
            continue;
        }
        break;
    }

    ul = 0;
    ioctl(handle, FIONBIO, &ul); //设置阻塞模式

    return count;
}
/*
*接收信息
*返回接收到的字节数
*/
int SocketClientEx::Receive(_out_ char* msg, unsigned int len, unsigned int timeout)
{
    if (!isconnected || handle == INVALID_SOCKET)
    {
        return 0;
    }

    int count = 0;
    FD_ZERO(&fdset);
    FD_SET(handle, &fdset);

    struct timeval timer;
    timer.tv_sec = timeout;
    timer.tv_usec = 0;

    int c = select(1, &fdset, NULL, NULL, &timer);
    if (c > 0)
    {
        count = recv(handle, msg, len, 0);
    }


    return count;
}
/*
*发送信息
*返回发送的字节数
*/
int SocketClientEx::Send(_in_ std::string &msg, unsigned int timeout)
{
    if (!isconnected || handle == INVALID_SOCKET)
    {
        return 0;
    }
    int count = 0;

    count=Send(msg.c_str(), msg.length(),timeout);

    return count;
}
/*
*发送信息
*返回发送的字节数
*/
int SocketClientEx::Send(const char* msg, unsigned int len, unsigned int timeout)
{
    if (!isconnected || handle == INVALID_SOCKET)
    {
        return 0;
    }

    //  char buff[1024] = { 0 };
    int count = 0;
    FD_ZERO(&fdset);
    FD_SET(handle, &fdset);

    struct timeval timer;
    timer.tv_sec = timeout;
    timer.tv_usec = 0;

    int c = select(handle + 1, NULL, &fdset, NULL, &timer);
    if (c > 0)
    {
        count = send(handle, msg, len, 0);
    }


    return count;

}


SocketClientEx::SEX_ERR_TYPE SocketClientEx::DisConnect()
{
    Reset();
    return SEX_NONE_ERR;
}

/*
*獲取對端的地址
*/
std::string SocketClientEx::GetPeerAddress()
{
    return this->address;
}

/*
*獲取對端的端口
*/
uint16_t SocketClientEx::GetPeerPort()
{
    return this->peerport;
}
/*
*獲取本地鏈接使用的端口
*/
uint16_t SocketClientEx::GetConnPort()
{
    return this->clientport;
}

void SocketClientEx::getuseport()
{
    struct sockaddr_in local;
    memset(&local,0,sizeof(local));
    socklen_t slen=sizeof(local);
    int ret= getsockname(this->handle,reinterpret_cast<struct sockaddr*>(&local),&slen);
    if(ret==0)
    {
        this->clientport=ntohs(local.sin_port);
    }

}
//通过已经建立连接的socket初始化一个客户端
int SocketClientEx::InitializeBySocket(int fd)
{
    Reset();
    struct sockaddr_in local;
    memset(&local,0,sizeof(local));
    socklen_t slen=sizeof(local);
    int ret= getpeername(fd,reinterpret_cast<struct sockaddr*>(&local),&slen);
    if(ret!=0)
    {
        return -1;
    }
    char ipaddr[20]={0};
    inet_ntop(AF_INET,&local.sin_addr.s_addr,ipaddr,sizeof(ipaddr));
    this->address=ipaddr;//服务端的地址

    this->peerport=ntohs(local.sin_port);//服务端的端口
    this->isconnected=true;
    this->handle=fd;

    getuseport();//获取客户端使用的端口

    return 0;
}

void SocketClientEx::Reset()
{
    if (handle != INVALID_SOCKET)
    {
        close(handle);
    }

    this->address.clear();
    this->peerport=0;
    this->clientport=0;
    this->handle=INVALID_SOCKET;
    FD_ZERO(&fdset);
    this->isconnected=false;
}


SocketClientEx::~SocketClientEx()
{
    if (handle != INVALID_SOCKET)
    {
        close(handle);
    }
#ifdef WIN32
    WSACleanup();
#endif
}
