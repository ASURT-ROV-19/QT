#include "gui.h"

gui::gui(QWidget *parent)
{
     timerLabel=new QLabel();
     timerLabel->setGeometry(0,0,50,50);
     pressureSensorLabel=new QLabel();
     updater=new QTimer();
     updater->setInterval(1000);
     updater->start();
     timer=new CountDown();
     vSpacer=new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Expanding);
     verLay=new QVBoxLayout();
     parent->setLayout(verLay);
     connect(updater,SIGNAL(timeout()),this,SLOT(updateTimer()));
     button=new QPushButton(parent);
     timer->setTimer(1,80);
     button->setText(timer->getTimeRemaining());
//     verLay->addWidget(button);
     verLay->addWidget(timerLabel);
     verLay->addWidget(pressureSensorLabel);
//     verLay->addSpacerItem(vSpacer);
     str=new gstream(parent,verLay);
//     str=new gstream(verLay,parent);
//     str=new gstream(parent);
//     verLay->addWidget(str->getRenderingWindow());

     str->action(parent,verLay);

}

void gui::updateTimer()
{
    button->setText(timer->getTimeRemaining());
    timerLabel->setText(timer->getTimeRemaining());
}
