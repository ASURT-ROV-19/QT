#include "joystick.h"
#define xAxis 0
#define yAxis 1
#define zAxis 3
#define rAxis 2
#define hat 0


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
    return SDL_JoystickGetAxis(js,xAxis);
}

int Joystick::get_y()
{
    return -SDL_JoystickGetAxis(js,yAxis);
}
int Joystick::get_z()
{
    return SDL_JoystickGetAxis(js,zAxis);
}
int Joystick::get_r()
{
    return SDL_JoystickGetAxis(js,rAxis);
}

int Joystick::getMapped_z()
{
    int Z=SDL_JoystickGetAxis(js,zAxis);
    return Z;
}

int Joystick::get_hat()
{
    return SDL_JoystickGetHat(js,hat);
}

void Joystick::activate()
{
    js= SDL_JoystickOpen(0);
//    qDebug()<< "joystick plugged";
}

void Joystick::remove()
{
    SDL_JoystickClose(js);
//    qDebug()<<"JS removed";
}

bool Joystick::message(QString msg)
{

    //True sends to GUI , while false sendes to server
    if (msg=="0"||msg=="1"||msg=="2"||msg=="3"||msg=="4"||msg=="5"){
        return true;
        }

    else
    return false;
}
