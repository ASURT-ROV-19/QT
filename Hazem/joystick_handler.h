#ifndef JOYSTICK_HANDLER_H
#define JOYSTICK_HANDLER_H

#include "joystick.h"
#include <QTimer>
#include <string.h>

using namespace std;

class Joystick_Handler: public QObject
{
    Q_OBJECT

public:
    Joystick_Handler();


public slots:
    void action();

private:
    Joystick *js;
    QTimer *timer;
    SDL_Event  event;
    int prev_x,prev_y,prev_z,prev_r;
    string msg;

signals:
    void msgsent(string);
};

#endif // JOYSTICK_HANDLER_H
