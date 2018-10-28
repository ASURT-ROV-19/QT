#ifndef JSINTERFACE_H
#define JSINTERFACE_H
#include "joystick.h"
#include "tcpsocket.h"
#include <QObject>

class JSInterface : public QObject
{
    Q_OBJECT
public:
    JSInterface();
private:
    joystick * controller;
    tcpsocket * piSock;
};

#endif // JSINTERFACE_H
