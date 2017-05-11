#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QtNetwork/QtNetwork>


class TcpServer : public QTcpServer
{
public:
    TcpServer();
  //  void incomingConnection(qintptr handle);//有新链接时的方法
private:
   QTcpSocket tcpClientSocket;
};

#endif // TCPSOCKET_H
