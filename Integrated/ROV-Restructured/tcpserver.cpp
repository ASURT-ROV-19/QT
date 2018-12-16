#include "tcpserver.h"


TCPServer::TCPServer(string Host,int Port)
{
    this->host=Host;
    this->port=Port;
    socket=new QTcpSocket;
    if(connectToServer()){
        connectionFlag=1;
        qDebug()<<"Connected";
    }
    //socket->connectToHost(host.c_str(),port);
    reConTimer=new QTimer;
    reConTimer->setInterval(200);
    connect(socket,SIGNAL(disconnected()),this,SLOT(reconnect()));
    connect(reConTimer,SIGNAL(timeout()),this,SLOT(reconnect()));
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()));


}

bool TCPServer::connectToServer()
{
    socket->connectToHost(host.c_str(),port);
//    qDebug()<<"Connected";
    return socket->waitForConnected(1000);
}

void TCPServer::reconnect()
{

    if(!connectionFlag){
        qDebug()<<"Disconnected";
//        connectionFlag=0;
        reConTimer->start();
        socket->connectToHost(host.c_str(),port);
    }
    qDebug()<<"Trying to reconnect";
    socket->connectToHost(host.c_str(),port);
    if (socket->waitForConnected(1000))
        connectionFlag=1;
}

void TCPServer::connected()
{

    if(connectionFlag){
        reConTimer->stop();
    }
    qDebug()<<"Connected";
}

//void TCPServer::sendmsg(QString message)
//{

//        qDebug()<<message;

//        socket->write(message.toStdString().c_str());
//}

void TCPServer::read()
{
    string s=socket->readAll().toStdString();
    emit receivedmsg(s);

}

bool TCPServer::isConnected()
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

bool TCPServer::sendToServer(QString message)
{
    if(isConnected()){
        socket->write(message.toUtf8());
        socket->flush();
        return true;
    }
    return false;
}

void TCPServer::sendMessage(QString message)

{
    try{
        if(/*socket->*/isConnected()){
            qDebug() << message;
            /*socket->*/sendToServer(message);
        }
        else if(/*socket->*/connectToServer()){
            if(socket->isReadable()){
                //setTCPConnection(tcpConnection);
                qDebug() <<"reconnected"<<  message;
                this->sendToServer(message);
            }
        }
    }
    catch(std::exception e){

    }
}

