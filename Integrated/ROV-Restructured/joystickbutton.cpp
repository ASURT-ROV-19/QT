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
    this->setText(name);
}

void joystickButton::initialDisplay()
{
    emit initialDisplaySign();
}

QString joystickButton::getName()
{
    return name;
}


void joystickButton::buttonClicked()
{
    emit thisClicked(this);
}
