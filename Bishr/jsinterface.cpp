#include "JS_PI_Interface.h"

JS_PI_Interface::JS_PI_Interface()
{
    controller=new joystick();
    piSock=new tcpsocket(this,2020);
    connect(controller ,SIGNAL(streamData(QString)),piSock,SLOT(setMessage(QString)));
    connect(controller ,SIGNAL(streamOrder(QString)),piSock,SLOT(setMessage(QString)));

}
