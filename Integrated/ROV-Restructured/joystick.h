#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QDebug>
#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>
#include <QTimer>
#include <string.h>
#include <QString>
using namespace std;


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
    int prev_x,prev_y,prev_z,prev_r,upZ=1,light=0;
    QString msg;
    void move();
    int mapZ();
    int map(int x);
    SDL_Joystick *js;
//    Joystick_Handler *handler;

public slots:
    void action();

signals:
    void sendMsg(QString);
//    void sendToServer(QString);
//    void sendToGUI(QString);

};


#endif // JOYSTICK_H
