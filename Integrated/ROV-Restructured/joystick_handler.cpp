#include "joystick_handler.h"

#define X js->get_x()
#define Y js->get_y()
#define Z js->get_z()
#define R js->get_r()
#define cam js->get_hat()
#define DEADZONE 4000
#define SGNFCNT 300

Joystick_Handler::Joystick_Handler()
{
    js=new Joystick;
    prev_x=prev_r=prev_y=prev_z=0;
    timer =new QTimer;
    timer->setInterval(50);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(action()));


}



void Joystick_Handler::action()
{
    while (SDL_PollEvent(&event)){
    switch (event.type){
    case SDL_JOYAXISMOTION:
        if (abs(X-prev_x)>SGNFCNT || abs(Y-prev_y)>SGNFCNT || abs(Z-prev_z)>SGNFCNT || abs(R-prev_r)>SGNFCNT){
            msg="";
            msg+="x="+((abs(X)>DEADZONE)?QString::number(X):"0") +",";
            msg+="y="+((abs(Y)>DEADZONE)?QString::number(Y):"0") +",";
            msg+="z="+QString::number(mapZ())+",";
            msg+="r="+((abs(R)>DEADZONE)?QString::number(R):"0") +",";
            msg+="cam="+QString::number(cam)+",";
            emit sendToServer(msg);

        }
        break;
    case SDL_JOYDEVICEADDED:
        js->activate();
        break;
    case SDL_JOYDEVICEREMOVED:
        js->remove();
        break;
    case SDL_JOYBUTTONDOWN:
        msg=QString::number(event.jbutton.button);
//        if (msg=="1"){
//            emit timerPause_Play(msg);
//        }
        //the next if case decides whether we are sending to server or making a change in GUI
        if(msg=="10"){

            (upZ==1)? (upZ=-1) : (upZ=1);
        }
        else if(js->message(msg))
            emit sendToGUI(msg);
        else
            emit sendToServer(msg);
        break;
    case SDL_JOYHATMOTION:
        msg="";
        msg+="x="+((abs(X)>DEADZONE)?QString::number(X):"0") +",";
        msg+="y="+((abs(Y)>DEADZONE)?QString::number(Y):"0") +",";
        msg+="z="+QString::number(mapZ())+",";
        msg+="r="+((abs(R)>DEADZONE)?QString::number(R):"0") +",";
        msg+="cam="+QString::number(cam)+",";
//        qDebug()<<msg;
        emit sendToServer(msg);
        break;
    default:
        break;
                       }

    }
}

int Joystick_Handler::mapZ()
{
    if(abs(Z)>DEADZONE)
        return upZ==1 ? (Z*101/(32768*2)+50) : -1* (100-(Z*101/(32768*2)+50)) ;
    else
        return 0;
}
