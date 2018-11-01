#ifndef JS_PI_INTERFACE_H
#define JS_PI_INTERFACE_H
#include "joystick.h"
#include "tcpsocket.h"
#include <QObject>

class JS_PI_Interface : public QObject
{
    Q_OBJECT
public:
    JS_PI_Interface();
private:
    joystick * controller;
    tcpsocket * piSock;
};

#endif // JS_PI_INTERFACE_H
