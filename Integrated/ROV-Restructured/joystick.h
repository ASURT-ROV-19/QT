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
    bool checkIfGuiButton(int button);
    void buttonDown(int button);
    void buttonUp(int button);

private:
    QTimer *timer;
    SDL_Event  event;
    int prev_x,prev_y,prev_z,prev_r,upZ=1,light=0,axisChangeFlag=0,activateR=0;
    int x,y,z,r;
    int upZButton=0,activateRButton=1,lightButton=6
            ;
    QString msg;
    void change_prev();
    void move();
    int mapZ();
    int map(int x);
    SDL_Joystick *js;

public slots:
    void action();
    void newButtonsConfig(QString newConfig);
signals:
    void sendMsg(QString);

};


#endif // JOYSTICK_H
