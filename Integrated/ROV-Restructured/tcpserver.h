#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <string.h>
#include<QDebug>
#include <QString>
using namespace std;
class TCPServer:public QObject
{
    Q_OBJECT
public:
    TCPServer(string Host,int Port);
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
    void sendmsg(QString message);
    void read();


};

#endif // TCPSERVER_H
