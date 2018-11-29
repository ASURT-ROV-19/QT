#include "joystick_handler.h"

#define X js->get_x()
#define Y js->get_y()
#define Z js->get_z()
#define R js->get_r()
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
            msg+="X="+((abs(X)>DEADZONE)?QString::number(X):"0") +",";
            msg+="Y="+((abs(Y)>DEADZONE)?QString::number(Y):"0") +",";
            msg+="Z="+((abs(Z)>DEADZONE)?QString::number(Z):"0") +",";
            msg+="R="+((abs(R)>DEADZONE)?QString::number(R):"0") +",";
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
        if(js->message(msg))
            emit sendToGUI(msg);
        else
            emit sendToServer(msg);
        break;
    default:
        break;
                       }

                               }
}
