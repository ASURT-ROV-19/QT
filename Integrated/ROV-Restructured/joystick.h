#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QDebug>
#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>



class Joystick:public QObject
{
    Q_OBJECT
   public:
    Joystick();

    int get_x();
    int get_y();
    int get_z();
    int get_r();
    void activate();
    void remove();

   private:
    SDL_Joystick *js;

};

#endif // JOYSTICK_H
