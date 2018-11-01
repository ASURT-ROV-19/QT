#include "gui.h"

gui::gui(QWidget *parent)
{
     timerLabel=new QLabel();
     timerLabel->setGeometry(0,0,500,500);
     timerLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
     pressureSensorLabel=new QLabel();
     updater=new QTimer();
     updater->setInterval(1000);
     updater->start();
     timer=new CountDown();
     verLay=new QVBoxLayout();
     parent->setLayout(verLay);
     parent->setStyleSheet("background-color: cyan");
     button=new QPushButton();
     connect(button,SIGNAL(clicked()),timer,SLOT(pause()));
     connect(updater,SIGNAL(timeout()),this,SLOT(updateTimer()));
     timer->setTimer(1,80);
     verLay->addWidget(button);
     verLay->addWidget(timerLabel);
     button->setText("Stop/Start Timer");
     verLay->addWidget(pressureSensorLabel);
     str=new gstream(parent,verLay);


}

void gui::updateTimer()
{
    timerLabel->setText(timer->getTimeRemaining());
}


