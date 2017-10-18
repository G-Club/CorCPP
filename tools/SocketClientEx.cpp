#include "SocketClientEx.h"

SocketClientEx::SocketClientEx() :isconnected(false)
{

#ifdef WIN32

	WORD sversion = MAKEWORD(2, 2);
	WSADATA data;
	WSAStartup(sversion, &data);

#endif

	handle = INVALID_SOCKET;
}

int SocketClientEx::Init()
{
	this->handle = socket(PF_INET, SOCK_STREAM, S_PROTO_TCP);
	if (SEX_INVALID_SOCKET == this->handle)
	{
		std::cout << "create socket error" << std::endl;
		return -1;
	}

	return 0;
}

SEX_ERR_TYPE  SocketClientEx::Connect2(std::string &ip, unsigned short port, unsigned int timeout)
{
	if (SEX_INVALID_SOCKET == handle)
	{
		std::cout << " socket handle error" << std::endl;
		return SEX_ERR_TYPE::SEX_ERROR;
	}

	int ret;
	sockaddr_in serv;
	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &serv.sin_addr);
	//serv.sin_addr.S_un.S_addr = inet_addr("192.168.0.162");

	SEX_ERR_TYPE errc = SEX_ERR_TYPE::SEX_NONE_ERR;

	unsigned long ul = 1;

	do
	{
		ioctl(handle, FIONBIO, &ul); //设置为非阻塞模式

		ret = connect(handle, (struct sockaddr*)&serv, sizeof(serv));
		int ecode = Errcode;
		if (ret == -1 && ecode == SEX_EINPROGRESS)
		{
			struct timeval timer;
			timer.tv_sec = timeout;
			timer.tv_usec = 0;

			FD_ZERO(&fs);
			FD_SET(handle, &fs);
			/*
			select会阻塞直到检测到事件或则超时，如果超时，select会返回0，
			如果检测到事件会返回1，如果异常会返回-1，如果是由于信号中断引起的异常errno==EINTR
			*/
			ret = select(0, NULL, &fs, NULL, &timer);
			if (ret == 0)
			{
				errc = SEX_ERR_TYPE::SEX_TIME_OUT;
				break;
			}
			isconnected = true;
		}
		else if (ret == -1)
		{
			errc = SEX_ERR_TYPE::SEX_ERROR;
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
int SocketClientEx::Receive(std::string &msg, unsigned int timeout)
{
	if (!isconnected || handle == INVALID_SOCKET)
	{
		return 0;
	}
	char buff[1024] = { 0 };
	int count = 0;
	FD_ZERO(&fs);
	FD_SET(handle, &fs);

	unsigned long ul = 1;
	ioctl(handle, FIONBIO, &ul); //设置为非阻塞模式
 
	while (1)
	{
		memset(buff, 0, sizeof(buff));
		int c = 0;
		c = Receive(buff, sizeof(buff), timeout);
		if (c > 0)
		{
			msg.append(buff, c);
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
int SocketClientEx::Receive(char* msg, unsigned int len, unsigned int timeout)
{
	if (!isconnected || handle == INVALID_SOCKET)
	{
		return 0;
	}

	int count = 0;
	FD_ZERO(&fs);
	FD_SET(handle, &fs);

	struct timeval timer;
	timer.tv_sec = timeout;
	timer.tv_usec = 0;

	int c = select(1, &fs, NULL, NULL, &timer);
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
int SocketClientEx::Send(std::string &msg, unsigned int timeout)
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

	char buff[1024] = { 0 };
	int count = 0;
	FD_ZERO(&fs);
	FD_SET(handle, &fs);

	struct timeval timer;
	timer.tv_sec = timeout;
	timer.tv_usec = 0;

	int c = select(1, NULL, &fs, NULL, &timer);
	if (c > 0)
	{
		count = send(handle, msg, len, 0);
	}


	return count;

}


SEX_ERR_TYPE SocketClientEx::DisConnect()
{
	if (handle != INVALID_SOCKET)
	{
		close(handle);
	}
	return SEX_NONE_ERR;
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
