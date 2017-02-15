#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QtNetwork/QtNetwork>



class TcpSocket : public QTcpSocket
{
public:
    TcpSocket();
};

#endif // TCPSOCKET_H
