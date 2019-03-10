#include "transparentlabel.h"

transparentLabel::transparentLabel()
{
    this->setText("depth=0");
    this->setStyleSheet("QLabel{color: white ;  font-size: 22px; }");
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setGeometry(0,0,120,120);
    this->show();

}
