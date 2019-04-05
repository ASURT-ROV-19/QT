#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <string.h>
#include<QDebug>
#include <QString>
#include <QHostAddress>
#include <exception>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

using namespace std;
class TCPConnection:public QObject
{
    Q_OBJECT
public:
    TCPConnection(string Host,int Port);
    bool isConnected();
    bool sendToServer(QString message);
    bool connectToServer();

public slots:
    void sendMessage(QString message); //Use this one
//    void connected();
private slots:
    void socketDisconnected();
    void socketErrorRaised(QAbstractSocket::SocketError error);
    void read();
private:
    QTcpSocket *socket;
    int connectionFlag,port;
    string host;
    QTimer * reconnectTimer;
signals:
    void receivedmsg(QString);

};

#endif // TCPSERVER_H
