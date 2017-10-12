#include "SocketClientEx.h"

SocketClientEx::SocketClientEx()
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
		ioctl(handle, FIONBIO, &ul); //����Ϊ������ģʽ

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
			select������ֱ����⵽�¼�����ʱ�������ʱ��select�᷵��0��
			�����⵽�¼��᷵��1������쳣�᷵��-1������������ź��ж�������쳣errno==EINTR
			*/
			ret = select(0, NULL, &fs, NULL, &timer);
			if (ret == 0)
			{
				errc = SEX_ERR_TYPE::SEX_TIME_OUT;
				break;
			}
		}
		else if (ret == -1)
		{
			errc = SEX_ERR_TYPE::SEX_ERROR;
			break;
		}

	} while (0);

	ul = 0;
	ioctl(handle, FIONBIO, &ul); //��������ģʽ

	return errc;
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
