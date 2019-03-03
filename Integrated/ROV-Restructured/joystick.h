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
    ~Joystick();
    void JoyStickInitialization();

    int get_x();
    int get_y();
    int get_z();
    int get_r();
    int get_hat();
    void activate();
    void remove();

public slots:
    void action();
signals:
    void axisMotion();
    void buttonPressed(int buttonNumber);
    void buttonReleased(int buttonNumber);

private:
    SDL_Joystick *js;
    QTimer *timer;
    SDL_Event * event;

};


#endif // JOYSTICK_H
