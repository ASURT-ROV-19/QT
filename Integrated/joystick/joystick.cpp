#include "joystick.h"
#define xAxis 0
#define yAxis 1
#define zAxis 3
#define rAxis 2
#define hat 0
#define Z_up 3
#define Z_down 1
#define light_On_Off 2
#define r_active 0


#define X this->get_x()
#define Y this->get_y()
#define Z this->get_z()
#define R this->get_r()
#define cam this->get_hat()
#define DEADZONE 4000
#define SGNFCNT 400


Joystick::Joystick()
{

    event=new SDL_Event();
    qDebug()<<"JOYSTICK CREATED";
    JoyStickInitialization();
    timer =new QTimer();
    timer->setInterval(50);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(action()));
}

Joystick::~Joystick()
{
    qDebug()<<"destroying joystick instance";
    SDL_JoystickClose(js);
    delete timer;

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
    return -SDL_JoystickGetAxis(js,zAxis);
}
int Joystick::get_r()
{
    return SDL_JoystickGetAxis(js,rAxis);
}

int Joystick::get_hat()
{
    return SDL_JoystickGetHat(js,hat);
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




void Joystick::JoyStickInitialization()
{

    SDL_Init(SDL_INIT_JOYSTICK);
//    SDL_Init(SDL_INIT_EVERYTHING);
//    SDL_Init(SDL_INIT_EVENTS);
     if (SDL_INIT_JOYSTICK<0){
         qDebug()<<"failed to init";
        return;
     }

     js = SDL_JoystickOpen(0);
//     SDL_JoystickEventState(SDL_ENABLE);

     if (SDL_JoystickGetAttached(js)){
         qDebug() <<"attached";
     qDebug() <<"Num of buttons is : "<<SDL_JoystickNumButtons(js);
     qDebug()<<"Num of hats is : " <<SDL_JoystickNumHats(js);
     qDebug() <<"num of axes is :" <<SDL_JoystickNumAxes(js);
     qDebug() <<"num of balls is :" <<SDL_JoystickNumBalls(js); }
}

void Joystick::action()
{
    while (SDL_PollEvent(event)){
        switch (event->type){
        case SDL_JOYAXISMOTION:
            emit axisMotion();
            break;
        case SDL_JOYDEVICEADDED:
            this->activate();
            break;
        case SDL_JOYDEVICEREMOVED:
            this->remove();
            break;
        case SDL_JOYBUTTONDOWN:
            emit buttonPressed(event->jbutton.button);
            break;
        case SDL_JOYBUTTONUP:
            emit buttonReleased(event->jbutton.button);
            break;
        case SDL_JOYHATMOTION:
            emit hatMotion();
            break;
        default:
            break;
        }

    }
}

