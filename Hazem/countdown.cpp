#include "countdown.h"

Countdown::Countdown(QMainWindow* window)
{


    counter=new QPushButton(window);
    text=new QPushButton(window);
    text->setText("Remainig Time");
    QFont font1=text->font();
    font1.setPointSize(8);
    text->setFont(font1);
    text->setGeometry(0,20,100,50);
    s="15:00";
    minutes=14,seconds=59;
    counter->setText(s.c_str());
    QFont font2=counter->font();
    font2.setPointSize(16);
    counter->setFont(font2);
    counter->setGeometry(0,60,100,100);
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000);


}

void Countdown::update()
{
     s=to_string(minutes)+":"+(seconds<10?"0"+to_string(seconds):to_string(seconds));
    counter->setText(s.c_str());
    seconds--;
    if(seconds<0)
        minutes--,seconds=59;
}
