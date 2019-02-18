#include "joystick_handler.h"

Joystick_Handler::Joystick_Handler()
{
    qDebug()<<"JOYSTICK HANDLER CREATED";

    joyS=new Joystick();
    connect(joyS,SIGNAL(sendMsg(QString)),this,SLOT(messageReceive(QString)));
}

void Joystick_Handler::changeInButtonsConfiguration(QString newConfig)
{
    joyS->changeInButtonsConfiguration(newConfig);
}



void Joystick_Handler::messageReceive(QString message)
{
//THESE NUMBERS ARE JOYSTICK BUTTONS' NUMBERS . IF CLICKED , THEN CHANGE IS IN GUI , NOT PI
/*************                                     ATTENTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!             *****************/
    //needs to be variable instead of hard coded numbers to cope with the flexibility of configuring buttons
    if (message=="0"||message=="1"||message=="2"||message=="3"||message=="4"){
        emit sendToGUI(message);
    }

    else{
        emit sendToPi(message);
        qDebug()<<message;
        }

}

// to be done to handle changes in buttons associated with pi




//void Joystick_Handler::getMessage(QString message, int serverOrGui)
//{
//    this->msg = message;
//    if(serverOrGui == 1) //wants to send to server
//    {
//        emit sendToServer(msg);
//    }
//    else if(serverOrGui == 0) //wants to send to GUI
//    {
//        emit sendToGUI(msg);
//    }
//}
