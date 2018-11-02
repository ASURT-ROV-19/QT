#include "tcpserver.h"

TCPServer::TCPServer(string Host,int Port)
{
    host=Host,port=Port;
    socket=new QTcpSocket;
    socket->connectToHost(host.c_str(),port);
    connectionFlag=1;
    reConTimer=new QTimer;
    reConTimer->setInterval(200);
    connect(socket,SIGNAL(disconnected()),this,SLOT(reconnect()));
    connect(reConTimer,SIGNAL(timeout()),this,SLOT(reconnect()));
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()));


}

void TCPServer::reconnect()
{

    if(connectionFlag){
        qDebug()<<"Disconnected";
        connectionFlag=0;
        reConTimer->start();

    }
    qDebug()<<"Trying to reconnect";
    socket->connectToHost(host.c_str(),port);

}

void TCPServer::connected()
{

    if(!connectionFlag){
        connectionFlag=1;
        reConTimer->stop();
    }
    qDebug()<<"Connected";
}

void TCPServer::sendmsg(string s)
{
        qDebug()<<s.c_str();
        socket->write(s.c_str());
}

void TCPServer::read()
{
    string s=socket->readAll().toStdString();
    emit receivedmsg(s);

}
