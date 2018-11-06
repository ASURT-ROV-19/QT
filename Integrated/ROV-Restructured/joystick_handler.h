#ifndef JOYSTICK_HANDLER_H
#define JOYSTICK_HANDLER_H
#include "joystick.h"
#include <QTimer>
#include <string.h>
#include <QString>
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
    QString msg;

signals:
    void sendToServer(QString);
    void sendToGUI(QString);

};

#endif // JOYSTICK_HANDLER_H
