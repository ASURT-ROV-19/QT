#include "transparentlabel.h"

transparentLabel::transparentLabel(int x, int y, int width, int height, QString color, QString fontSize, Qt::AlignmentFlag vertical, Qt::AlignmentFlag horizontal)
{
    this->setText("depth=0");
    this->setStyleSheet("QLabel{color: "+color+" ;  font-size: "+fontSize+"px; }");
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setGeometry(x,y,width,height);
    this->show();
    this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    this->setAlignment(horizontal);
    this->setAlignment(vertical);

}

transparentLabel::transparentLabel(QString color, QString fontSize, Qt::AlignmentFlag vertical, Qt::AlignmentFlag hotizontal)
{

    this->setText("depth=0");
    this->setStyleSheet("QLabel{color: "+color+" ;  font-size: "+fontSize+"px; }");
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setGeometry(0,0,120,120);
    this->show();
    this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    this->setAlignment(hotizontal);
    this->setAlignment(vertical);
}

