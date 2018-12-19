#include "joystick_handler.h"

Joystick_Handler::Joystick_Handler()
{

}


void Joystick_Handler::getMessage(QString message, int serverOrGui)
{
    this->msg = message;
    if(serverOrGui == 1) //wants to send to server
    {
        emit sendToServer(msg);
    }
    else if(serverOrGui == 0) //wants to send to GUI
    {
        emit sendToGUI(msg);
    }
}

