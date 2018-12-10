#include "joystickbutton.h"

joystickButton::joystickButton()
{

}

joystickButton::joystickButton(QString name, QString buttonNumber)
{
    this->name=name;
    this->number=number;
}

void joystickButton::setInfo(QString name, QString buttonNumber)
{
    this->name=name;
    this->number=number;
}

void joystickButton::initialDisplay()
{
    emit initialDisplaySign();
}

QString joystickButton::getName()
{
    return name;
}

void joystickButton::thisClicked(joystickButton **joyButtons, joystickButton **adminButtons, QRadioButton **selectionButtons)
{
    for (int i=0;i<6;i++){
        if (joyButtons[i]!=this){
            joyButtons[i]->hide();
        }
    }

    for (int i=0;i<6;i++){
        adminButtons[i]->show();
    }

}
