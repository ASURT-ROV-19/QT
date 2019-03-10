#include "TCPConnection.h"


TCPConnection::TCPConnection(string Host,int Port)
{
    this->host=Host;
    this->port=Port;
    socket=new QTcpSocket();
    connectToServer();
    int enableKeepAlive = 1;
    int fd = socket->socketDescriptor();
    setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &enableKeepAlive,
                sizeof(enableKeepAlive));

    int maxIdle = 1; /* seconds */
    setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &maxIdle, sizeof(maxIdle));

    int count =2; // send up to 3 keepalive packets out, then disconnect if no response
    setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &count, sizeof(count));

    int interval = 1; // send a keepalive packet out every 2 seconds (after the
                      // 5 second idle period)
    setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(interval));


//    socket->setSocketOption(QAbstractSocket::SocketOption::KeepAliveOption,true);
//    socket->setSocketOption(QAbstractSocket::SocketOption::,true);
//    socket->setSocketOption(QAbstractSocket::SocketOption::LowDelayOption,true);
//    socket->setSocketOption(QAbstractSocket::SocketOption::KeepAliveOption,5);
//    socket->setSocketOption(QAbstractSocket::SocketOption::KeepAliveOption,5);
//    connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));
//    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
//    connect(socket,SIGNAL(readyRead()),this,SLOT(read()));


}

bool TCPConnection::connectToServer()
{
    try {
        socket->connectToHost(host.c_str(),port);
    } catch (std::exception e) {
        qDebug()<<"exception thrown in line 22 , exception is "<<e.what();
    }
    return socket->waitForConnected(1000);
}

/*             read function , not yet used feature     */
//void TCPServer::read()
//{
//    try {
//        QString s=socket->readAll();
//        emit receivedmsg(s);
//        qDebug()<<"received from client :::"<<s;

//    } catch (std::exception e) {
//        qDebug()<<"TCP exception at line 73 , reading received message grom server throws exception"<<e.what();
//    }

//}

bool TCPConnection::isConnected()
{
    try {
        return socket->state() == QAbstractSocket::ConnectedState;
    } catch (std::exception e) {
        qDebug()<<"TCP exception at line 83 , checking state of socket throws exception "<<e.what();
        return false;       //will tell : no connection if an exception happens , don't yet know if this is right or wrong , whether to return false or true
    }
}

bool TCPConnection::sendToServer(QString message)
{
        try {
            socket->write(message.toUtf8());
            socket->flush();
            return true;
        } catch (std::exception e) {
            qDebug()<<"TCP exception at line 96 , writting and flushing on a socket throw an exception "<<e.what();
        }
    return false;

}

void TCPConnection::sendMessage(QString message)
{
    qDebug()<<message;

        if(isConnected()){
            qDebug() << message;
            sendToServer(message);
        }
        else if(connectToServer()){
            qDebug() <<"reconnected"<<  message;
            this->sendToServer(message);
        }
        else {
//            qDebug()<<"couldn't send message";

        }
}

void TCPConnection::socketDisconnected()
{
    try {
        if (socket->waitForDisconnected(1000)){
            qDebug()<<socket->waitForDisconnected(1000);
            connectionFlag=0;
            }
    } catch (std::exception e) {
        qDebug()<<"TCP exception at line 116 , socket disconnected throw an exception "<<e.what();
    }
}

