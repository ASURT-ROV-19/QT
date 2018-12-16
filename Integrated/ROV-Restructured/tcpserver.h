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

using namespace std;
class TCPServer:public QObject
{
    Q_OBJECT
public:
    TCPServer(string Host,int Port);
    bool isConnected();
    bool sendToServer(QString message);
    bool connectToServer();
public slots:
    void sendMessage(QString message); //Use this one
private:
    QTcpSocket *socket;
    QTimer *reConTimer;
    int connectionFlag,port;
    string host;
signals:
    void receivedmsg(string);
 public slots:
    void reconnect();
    void connected();
    void read();

};

#endif // TCPSERVER_H
