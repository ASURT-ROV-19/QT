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
private slots:
    void socketDisconnected();
private:
    QTcpSocket *socket;
    int connectionFlag,port;
    string host;
signals:
    void receivedmsg(QString);
 public slots:
//    void connected();
//    void read();  // not yet used feature

};

#endif // TCPSERVER_H
