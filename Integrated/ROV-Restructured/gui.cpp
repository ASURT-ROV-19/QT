#include "gui.h"

gui::gui(QWidget *parent)
{
    timerLabel=new QLabel();
    timerLabel->setGeometry(0,0,100,100);
    pressureSensorLabel=new QLabel();
    updater=new QTimer();
    updater->setInterval(1000);
    updater->start();
    gridLay=new QGridLayout;
    QFont font1=timerLabel->font();
    font1.setPointSize(18);
    timerLabel->setFont(font1);
    timer=new CountDown();
    parent->setLayout(gridLay);
    parent->setStyleSheet("background-color: lime");
    timerLabel->setStyleSheet("background-color: red");
    button=new QPushButton();
    play_pause_button=new QPushButton("Play/Pause");
    endButton=new QPushButton("Quit program");
    connect(button,SIGNAL(clicked()),timer,SLOT(pause()));
    connect(this,SIGNAL(pause_play()),timer,SLOT(pause()));
    timerLabel->setText(timer->getTimeRemaining());
    connect(updater,SIGNAL(timeout()),this,SLOT(updateTimer()));
    timer->setTimer(0,15);
    button->setText("Stop/Start Timer");
    streamer=new gstreamer(parent,gridLay);
    connect(play_pause_button,SIGNAL(clicked()),streamer,SLOT(play_pause()));
    connect(endButton,SIGNAL(clicked()),streamer,SLOT(quitProgram()));
    gridLay->addWidget(button);
    gridLay->addWidget(play_pause_button);
    gridLay->addWidget(endButton);
    timerLabel->setAttribute(Qt::WA_TranslucentBackground);
    timerLabel->setStyleSheet("background:transparent;");
    timerLabel->setParent(streamer->getRenderingWindow(1));
}

void gui::startListening(QApplication * myApp)
{
    streamer->action(myApp);

}

QPushButton *gui::getChangingButton()
{
    return button;
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

    }
}

void gui::changeInGUI()
{
    streamer->setWindowsSize();
}



