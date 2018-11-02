#include "gui.h"

gui::gui(QWidget *parent)
{
     timerLabel=new QLabel();
     timerLabel->setGeometry(0,0,500,500);
     timerLabel->setStyleSheet("background-color: rgba(255, 255, 255, 10);");
     pressureSensorLabel=new QLabel();
     updater=new QTimer();
     updater->setInterval(1000);
     updater->start();
     QFont font1=timerLabel->font();
     font1.setPointSize(18);
     timerLabel->setFont(font1);
     timer=new CountDown();
     verLay=new QVBoxLayout();
     parent->setLayout(verLay);
     parent->setStyleSheet("background-color: lime");
     button=new QPushButton();
     connect(button,SIGNAL(clicked()),timer,SLOT(pause()));
     connect(this,SIGNAL(pause_play()),timer,SLOT(pause()));
     timerLabel->setText(timer->getTimeRemaining());
     connect(updater,SIGNAL(timeout()),this,SLOT(updateTimer()));
     timer->setTimer(1,80);
     verLay->addWidget(button);
//     verLay->addWidget(timerLabel);
     button->setText("Stop/Start Timer");
     verLay->addWidget(pressureSensorLabel);
     dummy=new QWidget();

     str=new gstream(parent,verLay);
     timerLabel->setParent(dummy);
//     dummy->setAttribute(Qt::WA_TranslucentBackground);
//     dummy->setStyleSheet("background:transparent;");
     dummy->setParent(str->getRenderingWindow(1));
//     str->getRenderingWindow(1)->setAttribute(Qt::WA_TranslucentBackground);
//     str->getRenderingWindow(1)->setStyleSheet("background:transparent;");
     str->action(timerLabel);



}

void gui::updateTimer()
{
    timerLabel->setText(timer->getTimeRemaining());
}

void gui::pause_play_Timer()
{
    emit pause_play();
}

