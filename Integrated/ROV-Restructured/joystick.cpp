#include "joystick.h"

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


Joystick::Joystick()
{

    qDebug()<<"JOYSTICK CREATED";
    JoyStickInitialization();
    prev_x=prev_r=prev_y=prev_z=0;
    timer =new QTimer;
    timer->setInterval(50);
    timer->start();
//    handler = new Joystick_Handler();
    connect(timer,SIGNAL(timeout()),this,SLOT(action()));
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
    return SDL_JoystickGetAxis(js,zAxis);
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


void Joystick::JoyStickInitialization()
{

    SDL_Init(SDL_INIT_JOYSTICK);
    SDL_Init(SDL_INIT_EVERYTHING);

     if (SDL_INIT_JOYSTICK<0)
         qDebug()<<"failed to init";
     SDL_JoystickEventState(SDL_ENABLE);

/*_____________________________________________________________________________*/


     js = SDL_JoystickOpen(0);
     SDL_JoystickEventState(SDL_ENABLE);


/*_____________________________________________________________________________*/

     if (SDL_JoystickGetAttached(js)){
         qDebug() <<"attached";
     qDebug() <<"Num of buttons is : "<<SDL_JoystickNumButtons(js);
     qDebug()<<"Num of hats is : " <<SDL_JoystickNumHats(js);
     qDebug() <<"num of axes is :" <<SDL_JoystickNumAxes(js);
     qDebug() <<"num of balls is :" <<SDL_JoystickNumBalls(js); }
}

void Joystick::action()
{
    while (SDL_PollEvent(&event)){
    switch (event.type){
    case SDL_JOYAXISMOTION:
        if (abs(X-prev_x)>SGNFCNT || abs(Y-prev_y)>SGNFCNT || abs(Z-prev_z)>SGNFCNT || abs(R-prev_r)>SGNFCNT){

            move();
//            handler->getMessage(msg,1);
            emit sendMsg(msg);
        }
        break;
    case SDL_JOYDEVICEADDED:
        this->activate();
        break;
    case SDL_JOYDEVICEREMOVED:
        this->remove();
        break;
    case SDL_JOYBUTTONDOWN:
        msg=QString::number(event.jbutton.button);
        qDebug()<<event.jbutton.button;


//the next if case decides whether we are sending to server or making a change in GUI or a joystick change
        if(msg=="5"){
            if (abs(mapZ())<=1)
                (upZ==1)? (upZ=-1) : (upZ=1);
        }

        else if(msg=="9"){

            light==1 ? light=0 : light=1;
        }
        else if(this->message(msg))
        {
            emit sendMsg(msg);
//            handler->getMessage(msg,0);
        }
        else
        {
            emit sendMsg(msg);
//            handler->getMessage(msg,1);
        }
        break;
    case SDL_JOYHATMOTION:

        move();

        emit sendMsg(msg);
//        handler->getMessage(msg,1);
        break;
    default:
        break;
    }

    }
}


void Joystick::move()
{

    msg="";

//no mapping
//    msg+="x="+((abs(X)>DEADZONE)?QString::number(X):"0") +",";
//    msg+="y="+((abs(Y)>DEADZONE)?QString::number(Y):"0") +",";
//    msg+="z="+((abs(Z)>DEADZONE)?QString::number(Z):"0") +",";
//    msg+="r="+((abs(R)>DEADZONE)?QString::number(R):"0") +",";
//    msg+="cam="+QString::number(cam)+",";
//    msg+="light=0,";

//mapped

    msg+="x="+((abs(X)>DEADZONE)? QString::number(map(X)) : "0" )+"," ;
    msg+="y="+((abs(Y)>DEADZONE)? QString::number(map(Y)) : "0" )+"," ;
    msg+="z="+QString::number(mapZ())+",";
    msg+="r="+((abs(R)>DEADZONE)? QString::number(map(R)) : "0" )+"," ;
    msg+="cam="+QString::number(cam)+",";
    msg+="light="+QString::number(light)+",";




}


int Joystick::mapZ()
{
        return upZ * (Z*101/(32768*2)+50) ;
}


int Joystick::map(int x)
{
    return  x*100/32768 ;
}

