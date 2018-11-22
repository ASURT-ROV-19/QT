#include "gui.h"

gui::gui(QWidget *parent)
{
    gridLay=new QGridLayout;
    parent->setLayout(gridLay);
    parent->setStyleSheet("background-color: lime");

    butConfig =new buttonsConfiguration;
    connect(butConfig,SIGNAL(newSettings(QString)),this,SLOT(changeButtonsConfiguration(QString)));
    button=new QPushButton();
    button->setText("Stop/Start Timer");
    connect(button,SIGNAL(clicked()),butConfig,SLOT(show_hide()));

    endButton=new QPushButton("Quit program");
    timer=new CountDown();
    timer->setTimer(15,0);
    connect(button,SIGNAL(clicked()),timer,SLOT(pause_Play()));
    connect(this,SIGNAL(pause_play()),timer,SLOT(pause_Play()));
    gridLay->addWidget(timer->getTimerLabel(),0,0);

//    play_pause_button=new QPushButton("Play/Pause");

    gridLay->addWidget(button);

}

QPushButton *gui::getChangingButton()
{
    return button;
}

QGridLayout *gui::getLayout()
{
    return gridLay;
}

void gui::addWidgetToLayout(QWidget *window, uint8_t row, uint8_t col, uint8_t width, uint8_t height,uint8_t windowNumber)
{
    switch (windowNumber) {
    case 1:
        window1=window;
        gridLay->addWidget(window1,row,col,width,height);
        break;
    case 2:
        window2=window;
        gridLay->addWidget(window2,row,col,width,height);
        break;
    case 3:
        window3=window;
        gridLay->addWidget(window3,row,col,width,height);
        break;
    default:
        window1=window;
        gridLay->addWidget(window1,row,col,width,height);
        break;
    }
}

void gui::changeInGUI(QString button)
{
    if (button==timerButton)
        emit pause_play();
//
    else if(button==cameraButton)
        //do change in two windows sizes
    {

    }
    else if(button=="3")
        //quit
    {
        qDebug()<<"shall quit";

    }
    else if(button=="0")
        //play or pause
    {
        qDebug()<<"shall quit";

    }

}

void gui::changeButtonsConfiguration(QString newConfig)
{

    QString check=newConfig;
    check.chop(2);
    if (check=="camera button"){
        cameraButton=newConfig[newConfig.length()-1];
    }
    else if (check=="timer button"){
        timerButton=newConfig[newConfig.length()-1];
    }
    qDebug()<<newConfig<<"::"<<check<<"::"<<newConfig[newConfig.length()-1];
}




