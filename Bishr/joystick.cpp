#include "joystick.h"

joystick::joystick()
{

    timerJS=new QTimer(this);
    timerJS->setInterval(50);
    timerJS->start();
//    bttnPrint=new QPushButton(this);
//    bttnPrint->setText("Print Variables");
    connect(timerJS,SIGNAL(timeout()),this,SLOT(JSLoop()));
    SDL_Init(SDL_INIT_JOYSTICK);
    if (SDL_INIT_JOYSTICK<0){
        qDebug()<<"failed to intialize";}
    js=SDL_JoystickOpen(0);
    SDL_JoystickEventState(SDL_ENABLE);
    event = new SDL_Event;

}




void joystick::JSLoop()
{

    while (SDL_PollEvent(event)){
        switch(event->type){
            case SDL_JOYAXISMOTION:
                if (event->jaxis.axis==0){
                    if (map(event->jaxis.value)>x+3){
                        x=map(event->jaxis.value);
                        info+="X="+QString::number(x);
                        JSDataReady(info);
                }
                }
                else if (event->jaxis.axis==1){
                    if (map(event->jaxis.value)>y+3){
                    y=-1*map(event->jaxis.value);
                    info+="Y="+QString::number(y);
                    JSDataReady(info);
                    }
                }
                else if (event->jaxis.axis==2){
                 if (map(event->jaxis.value)>x+3){
                    z=map(event->jaxis.value);
                    info+="Z="+QString::number(z);
                    JSDataReady(info);
                 }
                }
                else if (event->jaxis.axis==3){
                 if (map(event->jaxis.value)>x+3){
                    r=map(event->jaxis.value);
                    info+="r="+QString::number(r);
                    JSDataReady(info);
                 }
                }

            /*________________________________________________________________________________________________________*/
/*
            if (abs(map(SDL_JoystickGetAxis(js,0)))>abs(x)+4){
                x=map(SDL_JoystickGetAxis(js,0));
                change=1;
            }
            if (abs(map(SDL_JoystickGetAxis(js,1)))>abs(y)+4){
                change=1;
                y=map(SDL_JoystickGetAxis(js,1));
            }
            if (abs(map(SDL_JoystickGetAxis(js,2)))>abs(z)+4){
                change=1;
                z=map(SDL_JoystickGetAxis(js,2));
            }
            if (abs(map(SDL_JoystickGetAxis(js,3)))>abs(r)+4){
                r=map(SDL_JoystickGetAxis(js,3));
                change=1;
            }
            if (change==1){
                JSDataReady();
                change=0;
            }
*/
            /*________________________________________________________________________________________________________*/
                break;
//            case SDL_JoyBallEvent:

//                break;
            case SDL_JOYBUTTONDOWN:
                qDebug()<<event->jbutton.button;
                if (event->jbutton.button==2){
                    info="servo up";
                    JSOrderRead();
                }
                else if (event->jbutton.button==3){
                    info="servo down";
                    JSOrderRead();
                }
                else if (event->jbutton.button==1){
                    info="acoustic";
                    JSOrderRead();
                }
//                else if (event->jbutton.button==3){
//                    pist2Strike();
//                }
                break;

//            case SDL_JOYBUTTONUP:
//                if (event->jbutton.button==2){

//                }
//                else if (event->jbutton.button==3){

//                }
//                break;

//            case SDL_JOYHATMOTION:


//                break;
            case SDL_JOYDEVICEREMOVED:
                SDL_JoystickClose(js);
                qDebug()<<"JS removed";
                break;
            case SDL_JOYDEVICEADDED:
                    qDebug()<<"JS added";
                    SDL_Init(SDL_INIT_JOYSTICK);
                    js=SDL_JoystickOpen(0);
                    break;

        }
    }

}

void joystick::print()
{

}


int joystick::map(int value)
{
    if (abs(value) <1200){
        return 0;
    }
    else{
        value=round(value*(100)/(32768));
        if (value>100)
            value=100;
        else if (value<-100)
            value =-100;

        return value;
    }
}





void joystick::JSDataReady(QString messageToConvey){
    change=0;
//    info= QString::number(x) +"," +QString::number(y) +"," +QString::number(z) +"," +QString::number(r)+";";
    emit streamData(info);
    qDebug()<<info;
    info="";
}

void joystick::JSDataReady(){
    change=0;
    info= QString::number(x) +"," +QString::number(y) +"," +QString::number(z) +"," +QString::number(r)+";";
    emit streamData(info);
    qDebug()<<info;
    info="";
}
void joystick::JSOrderRead(){
    emit streamData(info);
    qDebug()<<info;
}
