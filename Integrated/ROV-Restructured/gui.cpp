#include "gui.h"

gui::gui(QWidget *parent)
{
    gridLay=new QGridLayout;
    parent->setLayout(gridLay);
    parent->setStyleSheet("background-color: lime");

    createButtons();
    handleSignals();
    createWindows();
    gridLay->addWidget(timer->getTimerLabel(),0,0);
    gridLay->addWidget(button);
    gridLay->addWidget(play_pause_button);
    camera=new gstream *[3];

}

QPushButton *gui::getChangingButton()
{
    return button;
}

QGridLayout *gui::getLayout()
{
    return gridLay;
}


void gui::getCam(gstream * Camera, uint8_t cameraNum)
{
    camera[cameraNum-1]=Camera;
    gridLay->addWidget(camera[cameraNum-1]->getRenderingWindow(),0,cameraNum-1);
}

void gui::changeInGUI(QString button)
{
    if (button==timerButton)
        emit pause_play();
//
    else if(button==cameraButton)
        //do change in two windows sizes
    {
        toggleCamera();
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

void gui::createWindows()
{
   window=new QWidget *[3];
   window[1]==nullptr ? qDebug()<<"null":qDebug()<<"created";
}

void gui::toggleCamera()
{
    if (windowSelector==0){
        //two windows of equal size
        if (window[0]!=nullptr){
            gridLay->removeWidget(window[0]);
            gridLay->addWidget(window[0],0,0);
        }
        if (window[1]!=nullptr){
        gridLay->removeWidget(window[1]);
//        gridLay->addWidget(window[1],0,1);
        }
        windowSelector++;
        g_print("Size 0\n");
    }
    else if (windowSelector==1){
        // Window 1 becomes the main camera window
//        changeDisplaySize(200,200);
        /*
        in the previous commented , function i was trying to have control over display size at the receiver , it hadn't worked yet
        but shall it work , it would make us able to change size of display without any change on the the raspberry pi
        */
        if (window[0]!=nullptr){
        gridLay->removeWidget(window[0]);
//        gridLay->addWidget(window[0],0,0,1,8);
        }
        if (window[1]!=nullptr){
        gridLay->removeWidget(window[1]);
        gridLay->addWidget(window[1],0,8,1,3);
        }
        windowSelector++;
        g_print("Size 1\n");
    }
    else if (windowSelector==2){
//        Window 2 becomes the main camera window
        if (window[0]!=nullptr){
        gridLay->removeWidget(window[0]);
//        gridLay->addWidget(window[0],0,0,1,3);
        }
        if (window[1]!=nullptr){
        gridLay->removeWidget(window[1]);
        gridLay->addWidget(window[1],0,3,3,8);
        }
        windowSelector-=2;
        g_print("Size 2\n");
    }

}

void gui::createButtons()
{
    butConfig =new buttonsConfiguration;
    button=new QPushButton("Stop/Start Timer");
    endButton=new QPushButton("Quit program");
    timer=new CountDown();
    timer->setTimer(15,0);
    play_pause_button=new QPushButton("Play/Pause");

}

void gui::handleSignals()
{
    connect(butConfig,SIGNAL(newSettings(QString)),this,SLOT(changeButtonsConfiguration(QString)));
    connect(button,SIGNAL(clicked()),butConfig,SLOT(show_hide()));
    connect(button,SIGNAL(clicked()),timer,SLOT(pause_Play()));
    connect(this,SIGNAL(pause_play()),timer,SLOT(pause_Play()));
    connect(play_pause_button,SIGNAL(clicked()),this,SLOT(toggleCamera()));
}




