#include "tcpserver.h"


TCPServer::TCPServer(string Host,int Port)
{
    this->host=Host;
    this->port=Port;
    socket=new QTcpSocket;
    reConTimer=new QTimer;
    reConTimer->setInterval(200);
//    reConTimer->start();
    reconnect();
    connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));
    connect(reConTimer,SIGNAL(timeout()),this,SLOT(reconnect()));
//    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()));


}

bool TCPServer::connectToServer()
{
    try {
        socket->connectToHost(host.c_str(),port);
    } catch (std::exception e) {

    }
    return socket->waitForConnected(150);
}

void TCPServer::reconnect()
{

    try {
        socket->connectToHost(host.c_str(),port);
    } catch (std::exception e) {
        qDebug()<<"TCP exception at line 40 , connection to host fails "<<e.what();
    }
    try {
        if (socket->waitForConnected(150)){
            reConTimer->stop();
            connectionFlag=1;
        }
        else
            reConTimer->start();

    } catch (std::exception e) {
        //probably if this happens it is because of a low duration of waiting to reconnect , we shall increase it and see what happens
        qDebug()<<"TCP exception at line 51 , waiting for getting connected to host throws exception "<<e.what();
    }


}

void TCPServer::read()
{
    try {
        string s=socket->readAll().toStdString();
        emit receivedmsg(QString::fromStdString(s));
        qDebug()<<"received from client :::"<<QString::fromStdString(s);

    } catch (std::exception e) {
        qDebug()<<"TCP exception at line 73 , reading received message grom server throws exception"<<e.what();
    }

}

bool TCPServer::isConnected()
{
    try {
        return socket->state() == QAbstractSocket::ConnectedState;
    } catch (std::exception e) {
        qDebug()<<"TCP exception at line 83 , checking state of socket throws exception "<<e.what();
        return false;       //will tell : no connection if an exception happens , don't yet know if this is right or wrong , whether to return false or true
    }
}

bool TCPServer::sendToServer(QString message)
{
    if(isConnected()){
        try {
            socket->write(message.toUtf8());
            socket->flush();
            return true;
        } catch (std::exception e) {
            qDebug()<<"TCP exception at line 96 , writting and flushing on a socket throw an exception "<<e.what();
        }
    }
    return false;
}

void TCPServer::sendMessage(QString message)

{
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

void TCPServer::socketDisconnected()
{
    try {
        if (socket->waitForDisconnected(150)){
            connectionFlag=0;
            reconnect();
        }
    } catch (std::exception e) {
        qDebug()<<"TCP exception at line 116 , socket disconnected throw an exception "<<e.what();
    }
}
