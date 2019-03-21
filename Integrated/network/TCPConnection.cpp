#include "TCPConnection.h"


TCPConnection::TCPConnection(string Host,int Port)
{
    this->host=Host;
    this->port=Port;
    socket=new QTcpSocket();
    connectToServer();

    connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(socketErrorRaised(QAbstractSocket::SocketError)));
}

bool TCPConnection::connectToServer()
{
    try {
        socket->connectToHost(host.c_str(),port);
    } catch (std::exception e) {
        qDebug()<<"exception thrown in line 22 , exception is "<<e.what();
    }
    socket->waitForConnected(400);
    int enableKeepAlive = 1;
    int fd = socket->socketDescriptor();
    qDebug()<<"keep alive : "<<setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &enableKeepAlive,
                sizeof(enableKeepAlive));

    int maxIdle = 1;  //  seconds
    qDebug()<<"keep idle : "<<setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &maxIdle, sizeof(maxIdle));

    int count =2; // send up to 3 keepalive packets out, then disconnect if no response
    qDebug()<<"keep count : "<<setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &count, sizeof(count));

    int interval = 1; // send a keepalive packet out every 2 seconds (after the
                      // 5 second idle period)
    qDebug()<<"keep interval : "<<setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(interval));
    int enable=1;
    qDebug()<<"set reusable address: "<<setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    qDebug()<<"set reusable port: "<<setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int));

//    int lingerDuration=1;
//    qDebug()<<"set linger: "<<setsockopt(fd, SOL_SOCKET, SO_LINGER, &lingerDuration, sizeof(SO_LINGER));


    return socket->waitForConnected(10);
}

void TCPConnection::read()
{
    try {
        QString s=socket->readAll();
        emit receivedmsg(s);
    } catch (std::exception e) {
        qDebug()<<"TCP exception at line 73 , reading received message grom server throws exception"<<e.what();
    }
}

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
            qDebug()<<"couldn't send message";

        }
}

void TCPConnection::socketDisconnected()
{
    qDebug()<<"disconnection detected";
    socket->close();
    qDebug()<<"state is : "<<socket->state();
}

void TCPConnection::socketErrorRaised(QAbstractSocket::SocketError error)
{
    qDebug()<<"\n\n\n\n error occured , error is "<<error<<"\n\n\n\n\n";
    if (error==QAbstractSocket::SocketTimeoutError || error==QAbstractSocket::UnknownSocketError || error==QAbstractSocket::ProxyConnectionTimeoutError || error==QAbstractSocket::NetworkError ){
        socket->disconnect();
        socket->waitForDisconnected(100);
    }
}

