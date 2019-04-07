#include "joystick_handler.h"
#define buttonsInUse 11
#define piButtonsInUse 9
//for magazine servo , use buttons 10 and 11
//this class shall hold a string buttons array of all buttons and index is each button's id , receive messages from configHandler , telling it of which ID now has which value
#define axisMax 32768
#define X joyS->get_x()*camOnFocus
#define Y joyS->get_y()*camOnFocus
#define Z joyS->get_z()
#define R joyS->get_r()*activateR
#define DEADZONE 4000
#define SGNFCNT 400
#define Z_up 3
#define Z_down 1
#define switchPID 2
#define r_active 0
#define z_mode 4
#define pulleyCW 5
#define pulleyCCW 6
#define microMove 7
#define endoscopeCamWindow 8

// 4 down , 1 up

Joystick_Handler::Joystick_Handler()
{
    zMode=0;    prev_x=0;   prev_y=0;   prev_z=0;   prev_r=0;   upZ=0;  getTemperature=0;   axisChangeFlag=0;   activateR=0;    cam=0;
    joyS=new Joystick();
    buttons=new int[piButtonsInUse];
    buttons[r_active]=0;
    buttons[Z_up]=4;
    buttons[Z_down]=2;
    buttons[switchPID]=8;
    buttons[z_mode]=7;
    buttons[pulleyCW]=5;
    buttons[pulleyCCW]=3;
    buttons[microMove]=11;
    buttons[endoscopeCamWindow]=10;
    pulley=0;micro=0;PID=0;hat=0;
    signalsHandler();
}

Joystick_Handler::~Joystick_Handler()
{
    qDebug()<<"destroying joystick_handler instance";
    delete [] buttons;
    delete joyS;
}

//void Joystick_Handler::changeInButtonsConfiguration(QString newConfig)
//{
//    QStringList buttonID=newConfig.split(" ");
//    int buttonIndex=buttonID[0].toInt();
//    buttons[buttonIndex]=buttonID[1].toInt();
//}

void Joystick_Handler::joyAxisMotion()
{
    if (abs(X-prev_x)>SGNFCNT || abs(Y-prev_y)>SGNFCNT || abs(Z-prev_z)>SGNFCNT || abs(R-prev_r)>SGNFCNT){
        move();
        messageReady(msg);
    }
}

void Joystick_Handler::joyHatMotion()
{
    hat =joyS->get_hat();
    if (hat!=0 && hat!=1 && hat!=4 && hat!=2 && hat!=8)
        return;
    checkMagazinePulleyConflict();
    move();
    emit sendToPi(msg);
}

void Joystick_Handler::updateCamOnFocus(int cam)
{
    camOnFocus=cam;
    qDebug()<<"updated cam on focus";
}

void Joystick_Handler::checkMagazinePulleyConflict()
{
    if (pulley==0)
        return ;
    if (hat==8|| hat==2){
        hat=0;
    }
    qDebug()<<"pulleyDirection getting updated";
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
    if(button==buttons[r_active])
    {
        activateR=1;
        return;
    }
    else if(button==buttons[switchPID]){
        zMode =!zMode;
        upZ=0;
        emit sendZDirection("-");
        PID=!PID;
        msg="PID="+QString::number(PID);
    }
    else if (button==buttons[Z_up]){
        if (upZ==1){
            upZ=0;
            emit sendZDirection("-");
        }
        else {
            upZ=-1;
            emit sendZDirection("↑");
        }
        move();
    }
    else if(button==buttons[Z_down])
    {
        if (upZ==-1){
            upZ=0;
            emit sendZDirection("-");
        }
        else {
            upZ=1;
            emit sendZDirection("↓");
        }
        move();
    }



    messageReady(msg);
    qDebug()<<"mode is "<<zMode<<"\n upZ is "<<upZ;

}

void Joystick_Handler::buttonUp(int button)
{
     if(button==buttons[r_active])
    {
        activateR=0;
        move();
        messageReady(msg);
    }
/*     else if (button==buttons[z_mode]){
         zMode =!zMode;
         upZ=0;
         emit sendZDirection("-");
         move();
     }
*/
     else if (button==buttons[pulleyCW]){
         pulley==1 ? pulley=0 : pulley =-1;
         checkMagazinePulleyConflict();
         emit sendToPi("Pulley "+QString::number(pulley));
         return ;
     }
     else if (button==buttons[pulleyCCW]){
         pulley==-1 ? pulley=0 : pulley =1;
         checkMagazinePulleyConflict();
         emit sendToPi("Pulley "+QString::number(pulley));
         return ;
     }
     else if(button==buttons[microMove]){
         micro=!micro;
         emit sendToPi("Micro_ROV "+QString::number(micro));
     }
     else if(button==buttons[endoscopeCamWindow]){
         showOrHideEndoscopeCamera();
     }


    if (zMode==1){
       if (button==buttons[Z_up]){
           upZ=0;
           emit sendZDirection("-");
       }
       else if(button==buttons[Z_down])
       {
           upZ=0;
           emit sendZDirection("-");
       }
       move();
       emit sendToPi(msg);
   }
    qDebug()<<"button up :: mode is "<<zMode<<"\n upZ is "<<upZ;
}


int Joystick_Handler::mapZ()
{
  return upZ*(Z*100/(axisMax*2)+49);
}

int Joystick_Handler::map(int axisValue)
{
   return  axisValue*100/axisMax ;
}

void Joystick_Handler::move()
{

    msg="";
    change_prev();
        //message for ROV19 Pi
    msg+="x="+((abs(X)>DEADZONE)? QString::number(map(X)) : "0" )+"," ;
    msg+="y="+((abs(Y)>DEADZONE)? QString::number(map(Y)) : "0" )+"," ;
    msg+="z="+QString::number(mapZ())+",";
    msg+="r="+((abs(R)>DEADZONE)? QString::number(map(R)) : "0" )+"," ;
    msg+="cam="+QString::number(hat)+"&";




    //message for ROV18 Pi
//    msg += " x " + QString("%1").arg(((abs(X)>DEADZONE)? map(X) : 0 ) ,3 , 10, QChar('0'));
//    msg += "; y " + QString("%1").arg(((abs(Y)>DEADZONE)? map(Y) : 0 ) ,3 , 10, QChar('0'));
//    msg += "; r " + QString("%1").arg(((abs(R)>DEADZONE)? map(R) : 0 ) ,3 , 10, QChar('0'));
//    msg += "; z " + QString("%1").arg(((abs(Z)>DEADZONE)? mapZ() : 0 ) ,3 , 10, QChar('0')) + "; ";
//    msg += "up "+ QString("%1").arg(upZ==1 ? upZ : 0 ,1,10, QChar('0')) + "; ";
//    msg += "down "+ QString("%1").arg(upZ==-1 ? -upZ : 0 ,1,10, QChar('0')) + " ;";
//    msg += " L " + QString("%1").arg( 0,1,10, QChar('0')) + "; ";
//    msg += "cam_up " + QString("%1").arg(0,1,10, QChar('0')) + "; ";
//    msg += "cam_down " + QString("%1").arg( 0,1,10, QChar('0')) + "; ";
//    msg += "mode 0;";
//    msg += " bag " + QString("%1").arg( 0,1,10, QChar('0')) + "; ";

}

void Joystick_Handler::signalsHandler()
{
    connect(joyS,SIGNAL(axisMotion()),this,SLOT(joyAxisMotion()));
    connect(joyS,SIGNAL(hatMotion()),this,SLOT(joyHatMotion()));
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

