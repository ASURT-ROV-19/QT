#include "gui.h"

gui::gui(QWidget *parent)
{
//    QWidget dummy;
     dummy =new QWidget(parent);
     timerLabel=new QLabel(parent);
     pressureSensorLabel=new QLabel(parent);
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
//     verLay->addSpacerItem(vSpacer);
     verLay->addWidget(timerLabel);
          verLay->addWidget(pressureSensorLabel);
     verLay->addSpacerItem(vSpacer);
     str=new gstream(parent);
      verLay->addWidget(dummy);
     verLay->addWidget(str->getRenderingWindow());
}

void gui::updateTimer()
{
    button->setText(timer->getTimeRemaining());
    timerLabel->setText(timer->getTimeRemaining());
}
