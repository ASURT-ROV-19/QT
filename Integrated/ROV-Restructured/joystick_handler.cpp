#include "joystick_handler.h"

Joystick_Handler::Joystick_Handler()
{
    qDebug()<<"JOYSTICK HANDLER CREATED";

    joyS=new Joystick();
    connect(joyS,SIGNAL(sendMsg(QString)),this,SLOT(messageReceive(QString)));
    buttons=new int[joyS->getNumOfPiButtons()];
    for (int i=0;i<joyS->getNumOfPiButtons();i++){
        buttons[i]=i;
    }
}

void Joystick_Handler::changeInButtonsConfiguration(QString newConfig)
{
    joyS->changeInButtonsConfiguration(newConfig);
    getButtons();
}

void Joystick_Handler::getButtons()
{
    qDebug()<<"in jsHandler line 23 , shall change local class pi buttons numbers";
    for (int i=0;i<joyS->getNumOfPiButtons();i++){
        buttons[i]=joyS->getButtonNumber(i);
    }
}



void Joystick_Handler::messageReceive(QString message)
{
//THESE NUMBERS ARE JOYSTICK BUTTONS' NUMBERS . IF CLICKED , THEN CHANGE IS IN GUI , NOT PI
/*************                                     ATTENTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!             *****************/

    if (message.length()>=4)
        emit sendToPi(message);
    else
        emit sendToGUI(message);

}

