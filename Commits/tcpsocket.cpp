#include "tcpsocket.h"

tcpsocket::tcpsocket(QObject *parent, quint16 port)
{
    sock=new QTcpSocket(parent);
    sock->connectToHost("169.254.168.225",port);

    connect(sock,SIGNAL(connected()),this,SLOT(connected()));
//    connect(sock,SIGNAL(()),this,SLOT(connected()));
    connect(sock,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(sock,SIGNAL(readyRead()),this,SLOT(readyRread()));
//    connect(sock,SIGNAL(bytesWritten(qint64))),this,SLOT(bytesWritten(qint64));
    if (!sock->waitForConnected(1000))
        qDebug()<<"Error : "<<sock->error();
    else {
        qDebug()<<"Connected successfully. ";
    }
    message=NULL;
}

void tcpsocket::sendOrder()
{
    sock->write(msg);
    sock->waitForBytesWritten(50);
}


void tcpsocket::setMessage(QString data)
{
    qDebug()<<data;
    msg=nullptr;
    msg=data.toLocal8Bit();
    message= msg.data();
    sendOrder();
//    elements= strlen(msg);
//    qDebug()<<"Length of message is "<<elements;
}


void tcpsocket::connected(){

    qDebug()<<"connection detected";
//    setMessage("Ready to send data");
    sendOrder();

}


void tcpsocket::disconnected(){
//    QHostAddress sender;
//    qDebug()<<"Client"<<sender.toString();

}


void tcpsocket::bytesWritten(qint64 bytes){
    qDebug()<<bytes;

}


void tcpsocket::readyRread(){


}


void tcpsocket::newConnection(){



}
