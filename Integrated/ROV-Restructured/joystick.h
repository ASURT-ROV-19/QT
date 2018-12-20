#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QDebug>
#include <SDL.h>
#include <SDL_joystick.h>
#include <QTimer>
#include <string.h>
#include <QString>
#include "joystick_handler.h"
using namespace std;

#define xAxis 0
#define yAxis 1
#define zAxis 3
#define rAxis 2
#define hat 0

#define X this->get_x()
#define Y this->get_y()
#define Z this->get_z()
#define R this->get_r()
#define cam this->get_hat()
#define DEADZONE 4000
#define SGNFCNT 300

class Joystick:public QObject
{
    Q_OBJECT
public:
    Joystick();
    void JoyStickInitialization();

    int get_x();
    int get_y();
    int get_z();
    int get_r();
    int getMapped_z();
    int get_hat();
    void activate();
    void remove();
    bool message(QString msg);

private:
    QTimer *timer;
    SDL_Event  event;
    int prev_x,prev_y,prev_z,prev_r,upZ=1;
    QString msg;
    int mapZ();
    SDL_Joystick *js;
    Joystick_Handler *handler;

public slots:
    void action();

//signals:
//    void sendToServer(QString);
//    void sendToGUI(QString);

};


#endif // JOYSTICK_H
