#include "joystick.h"

Joystick::Joystick()
{

    SDL_Init(SDL_INIT_JOYSTICK);
    SDL_Init(SDL_INIT_EVERYTHING);

     if (SDL_INIT_JOYSTICK<0)
         qDebug()<<"failed to init";
     SDL_JoystickEventState(SDL_ENABLE);

/*_____________________________________________________________________________*/


     js=SDL_JoystickOpen(0);
     SDL_JoystickEventState(SDL_ENABLE);


/*_____________________________________________________________________________*/

     if (SDL_JoystickGetAttached(js)){
         qDebug() <<"attached";
     qDebug() <<"Num of buttons is : "<<SDL_JoystickNumButtons(js);
     qDebug()<<"Num of hats is : " <<SDL_JoystickNumHats(js);
     qDebug() <<"num of axes is :" <<SDL_JoystickNumAxes(js);
     qDebug() <<"num of balls is :" <<SDL_JoystickNumBalls(js); }
}

int Joystick::get_x()
{
    return SDL_JoystickGetAxis(js,0);
}

int Joystick::get_y()
{
    return -SDL_JoystickGetAxis(js,1);
}
int Joystick::get_z()
{
    return SDL_JoystickGetAxis(js,3);
}
int Joystick::get_r()
{
    return SDL_JoystickGetAxis(js,2);
}

void Joystick::activate()
{
    js= SDL_JoystickOpen(0);
    qDebug()<< "joystick plugged";
}

void Joystick::remove()
{
    SDL_JoystickClose(js);
    qDebug()<<"JS removed";
}

void Joystick::message(QString msg)
{
    if (msg=="1"){

    }
}
