#include "joystickbutton.h"

joystickButton::joystickButton()
{
    name="";
    number="";
}

joystickButton::joystickButton(QString name, QString buttonNumber, QString id)
{
    this->name=name;
    this->number=buttonNumber;
    this->ID=id;
}

void joystickButton::setInfo(QString name, QString buttonNumber, QString id)
{
    this->name=name;
    this->number=number;
    this->setText(name);
    this->number=buttonNumber;
    this->ID=id;
}

void joystickButton::initialDisplay()
{
    emit initialDisplaySign();
}

QString joystickButton::getName()
{
    return name;
}

QString joystickButton::getNumber()
{
    return number;
}

QString joystickButton::getID()
{
    return ID;
}

void joystickButton::updateNumber(QString newNumber)
{
    this->number=newNumber;
}


void joystickButton::buttonClicked()
{
    emit thisClicked(this);
}
