#include "gui.h"

gui::gui(QWidget *parent)
{
    timerLabel=new QLabel();
    timerLabel->setGeometry(0,0,100,100);
    timerLabel->setStyleSheet("background-color: rgba(255, 255, 255, 10);");
    pressureSensorLabel=new QLabel();
    updater=new QTimer();
    updater->setInterval(1000);
    updater->start();
    gridLay=new QGridLayout;
    QFont font1=timerLabel->font();
    font1.setPointSize(18);
    timerLabel->setFont(font1);
    timer=new CountDown();
    verLay=new QVBoxLayout();
//    parent->setLayout(verLay);
    parent->setLayout(gridLay);
    parent->setStyleSheet("background-color: lime");
    timerLabel->setStyleSheet("background-color: red");
    button=new QPushButton();
    connect(button,SIGNAL(clicked()),timer,SLOT(pause()));
    connect(this,SIGNAL(pause_play()),timer,SLOT(pause()));
    timerLabel->setText(timer->getTimeRemaining());
    connect(updater,SIGNAL(timeout()),this,SLOT(updateTimer()));
    timer->setTimer(15,0);
    verLay->addWidget(button);
//     verLay->addWidget(timerLabel);
    button->setText("Stop/Start Timer");
    verLay->addWidget(pressureSensorLabel);
//     str=new gstream(parent,verLay);
    streamer=new gstreamer(parent,verLay);
//     verLay->addWidget(timerLabel);
     timerLabel->setParent(streamer->getRenderingWindow(1));
     timerLabel->setAttribute(Qt::WA_TranslucentBackground);
     timerLabel->setStyleSheet("background:transparent;");
//     verLay->insertWidget(1,timerLabel);

}

void gui::startListening(QApplication * myApp)
{
    streamer->action(myApp);
}


void gui::updateTimer()
{
    timerLabel->setText(timer->getTimeRemaining());
}

void gui::changeInGUI(QString button)
{
    if (button=="1")
        emit pause_play();
//
    else if(button=="2")
        //do change in two windows sizes
    {    streamer->setWindowsSize();
        qDebug()<<"afsdfsd";

    }
}



