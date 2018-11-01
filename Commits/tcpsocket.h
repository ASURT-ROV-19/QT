#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <string>
#include <QString>
#include <QTcpSocket>
#include <QDebug>
class tcpsocket : public QObject
{
    Q_OBJECT
public:
    tcpsocket(QObject * parent=0,quint16 port=12000);

public slots:
    void setMessage (QString data);
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRread();
    void newConnection();
    void sendOrder();
private:
    QTcpSocket * sock;
    char * message;
    QByteArray msg;
    int elements=0;
};

#endif // TCPSOCKET_H
