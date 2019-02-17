#include "joystickbutton.h"

joystickButton::joystickButton()
{
    name="";
    number="";
    item=new QTableWidgetItem;
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
    item->setText(name);
    this->setText(name);
    this->number=buttonNumber;
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

void joystickButton::updateNumber(QString newNumber)
{
    this->number=newNumber;
}

QTableWidgetItem *joystickButton::getItem()
{
    return item;
}


void joystickButton::buttonClicked()
{
    emit thisClicked(this);
}
