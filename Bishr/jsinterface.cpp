#include "jsinterface.h"

JSInterface::JSInterface()
{
    controller=new joystick();
    piSock=new tcpsocket(this,2020);
    connect(controller ,SIGNAL(streamData(QString)),piSock,SLOT(setMessage(QString)));
    connect(controller ,SIGNAL(streamOrder(QString)),piSock,SLOT(setMessage(QString)));
//    connect(controller,SIGNAL(getMapped()),piSock,SLOT(setMessage(char*)));
//    connect(controller,SIGNAL(streamData(QString)),piSock,SLOT(QString));
}
