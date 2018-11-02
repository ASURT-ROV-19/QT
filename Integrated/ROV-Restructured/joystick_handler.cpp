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
            msg+=((abs(X)>DEADZONE)?to_string(X):"0") +" ";
            msg+=((abs(Y)>DEADZONE)?to_string(Y):"0") +" ";
            msg+=((abs(Z)>DEADZONE)?to_string(Z):"0") +" ";
            msg+=(abs(R)>DEADZONE)?to_string(R):"0";
            emit msgsent(msg);
        }
        break;
    case SDL_JOYDEVICEADDED:
        js->activate();
        break;
    case SDL_JOYDEVICEREMOVED:
        js->remove();
    default:
        break;
                       }

                               }
}
