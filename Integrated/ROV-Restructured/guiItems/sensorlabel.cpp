#include "sensorlabel.h"

sensorLabel::sensorLabel()
{
    this->setText("depth=0");
    this->setStyleSheet("QLabel{color: red ;  font-size: 30px; }");
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setGeometry(0,0,120,120);

}
