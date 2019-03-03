#include "joystick_handler.h"
#define buttonsInUse 10
#define piButtonsInUse 4

#define axisMax 32768
#define X joyS->get_x()
#define Y joyS->get_y()
#define Z joyS->get_z()
#define R joyS->get_r()*activateR
#define cam joyS->get_hat()
#define DEADZONE 4000
#define SGNFCNT 400
#define Z_up 3
#define Z_down 1
#define light_On_Off 2
#define r_active 0



Joystick_Handler::Joystick_Handler()
{
    prev_x=0;prev_y=0;prev_z=0;prev_r=0;upZ=0;light=0;axisChangeFlag=0;activateR=0;
    joyS=new Joystick();
    buttons=new int[piButtonsInUse];
    for (int i=0;i<piButtonsInUse;i++){
        buttons[i]=i;
    }
    signalsHandler();
}

Joystick_Handler::~Joystick_Handler()
{
    qDebug()<<"destroying joystick_handler instance";
    delete [] buttons;
    delete joyS;
}

void Joystick_Handler::changeInButtonsConfiguration(QString newConfig)
{
    QStringList buttonID=newConfig.split(" ");
    int buttonIndex=buttonID[0].toInt();
    buttons[buttonIndex]=buttonID[1].toInt();
}

void Joystick_Handler::joyAxisMotion()
{
    if (abs(X-prev_x)>SGNFCNT || abs(Y-prev_y)>SGNFCNT || abs(Z-prev_z)>SGNFCNT || abs(R-prev_r)>SGNFCNT){
        move();
        messageReady(msg);
    }

}



void Joystick_Handler::messageReady(QString message)
{
    qDebug()<<message;
    if (message.length()>=4){
        emit sendToPi(message);
        return;
    }
    emit guiChange(message);
}

void Joystick_Handler::buttonDown(int button)
{
    msg=QString::number(button);
    qDebug()<<button;
    if (button==buttons[Z_up]){
        upZ=-1;
        buttonDownMessage();
    }
    else if(button==buttons[Z_down])
    {
        upZ=1;
        buttonDownMessage();
    }
    else if(button==buttons[light_On_Off]){
        light==1 ? light=0 : light=1;
        move();
    }
    else if(button==buttons[r_active])
    {
        activateR=1;
    }
    else
    {
        messageReady(msg);
        qDebug()<<"message of line 113->>"<<msg;
    }


}

void Joystick_Handler::buttonUp(int button)
{
    msg=QString::number(button);
    qDebug()<<button;
    if (button==buttons[Z_up]){
        upZ=0;
        buttonDownMessage();
    }
    else if(button==buttons[Z_down])
    {
        upZ=0;
        buttonDownMessage();
    }
    else if(button==buttons[r_active])
    {
        activateR=0;
    }
    else
    {
        messageReady(msg);
    }


}

void Joystick_Handler::buttonDownMessage()
{
    msg="";
    msg+="x="+QString::number(map(X))+"," ;
    msg+="y="+QString::number(map(Y))+"," ;
    msg+="z="+QString::number(mapZ())+",";
    msg+="r="+QString::number(map(R))+"," ;
    msg+="cam="+QString::number(cam)+",";
    msg+="light="+QString::number(light)+",";
    qDebug()<<msg;
    messageReady(msg);
}

void Joystick_Handler::buttonUpMessage()
{
    msg="";
    msg+="x="+QString::number(map(X))+"," ;
    msg+="y="+QString::number(map(Y))+"," ;
    msg+="z=0,";
    msg+="r="+QString::number(map(R))+"," ;
    msg+="cam="+QString::number(cam)+",";
    msg+="light="+QString::number(light)+",";
    qDebug()<<msg;
    messageReady(msg);

}

int Joystick_Handler::mapZ()
{
  return upZ * (Z*100/(axisMax*2)+50);
}

int Joystick_Handler::map(int axisValue)
{
   return  axisValue*100/axisMax ;
}

void Joystick_Handler::move()
{

    msg="";
    change_prev();

    msg+="x="+((abs(X)>DEADZONE)? QString::number(map(X)) : "0" )+"," ;
    msg+="y="+((abs(Y)>DEADZONE)? QString::number(map(Y)) : "0" )+"," ;
    msg+="z="+QString::number(mapZ())+",";
    msg+="r="+((abs(R)>DEADZONE)? QString::number(map(R)) : "0" )+"," ;
    msg+="cam="+QString::number(cam)+",";
    msg+="light="+QString::number(light)+",";

}

void Joystick_Handler::signalsHandler()
{
    connect(joyS,SIGNAL(axisMotion()),this,SLOT(joyAxisMotion()));
    connect(joyS,SIGNAL(buttonPressed(int)),this,SLOT(buttonDown(int)));
    connect(joyS,SIGNAL(buttonReleased(int)),this,SLOT(buttonUp(int)));
}

void Joystick_Handler::change_prev()
{
    prev_x=X;
    prev_y=Y;
    prev_z=Z;
    prev_r=R;
}

