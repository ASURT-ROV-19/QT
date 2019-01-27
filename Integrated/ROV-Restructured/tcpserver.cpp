#include "tcpserver.h"


TCPServer::TCPServer(string Host,int Port)
{
    this->host=Host;
    this->port=Port;
    socket=new QTcpSocket;
    if(connectToServer()){
        connectionFlag=1;
//        qDebug()<<"Connected";
    }
    else
//        qDebug()<<"NotConnected";
    //socket->connectToHost(host.c_str(),port);
    reConTimer=new QTimer;
    reConTimer->setInterval(200);
    reConTimer->start();
    connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));
    connect(reConTimer,SIGNAL(timeout()),this,SLOT(reconnect()));
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()));


}

bool TCPServer::connectToServer()
{
    try {
        socket->connectToHost(host.c_str(),port);
    } catch (std::exception e) {

    }

    //    qDebug()<<"Connected";
    return socket->waitForConnected(150);
}

void TCPServer::reconnect()
{

    try {
        socket->connectToHost(host.c_str(),port);
    } catch (std::exception e) {

    }
        if (socket->waitForConnected(150)){
            reConTimer->stop();
            connectionFlag=1;
        }
        else
            reConTimer->start();

}

void TCPServer::connected()
{

    if(connectionFlag){
        reConTimer->stop();
    }
//    qDebug()<<"Connected";
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

void TCPServer::socketDisconnected()
{
    connectionFlag=0;
//    qDebug()<<"Disconnected";
    reconnect();
}

