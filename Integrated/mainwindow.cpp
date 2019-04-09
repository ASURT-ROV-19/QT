#include "mainwindow.h"
#include "ui_mainwindow.h"
#define microCameraStartDelay 8000


MainWindow::MainWindow(QWidget *parent,QString processName, QString directory) :
    QMainWindow(parent)
{

    pulley=0;
    micro=0;
    this->show();
    this->setGeometry(100,100,800,600);
    TCPconnection=new TCPConnection("10.1.1.15",9005);
//    TCPconnection=new TCPConnection("127.0.0.1",9005);
    JSHandler = new Joystick_Handler();
    centralWidget=new QWidget();
    centralWidget->show();
    centralWidget->setWindowTitle("Stream");
    this->setCentralWidget(centralWidget);
    GUI=new gui(centralWidget,processName,directory);
    microDisplayDelayTimer=new QTimer();
    microDisplayDelayTimer->setInterval(microCameraStartDelay);
    signalsHandler();
}



void MainWindow::setDisplayWindow(QGst::Ui::VideoWidget * displayWindow,uint8_t cameraNum)
{
    GUI->setDisplayWindow(displayWindow,cameraNum);
}

void MainWindow::setEndoscopeCamera(gstreamer *camera)
{
    GUI->setEndoscopeCamera(camera);
}


MainWindow::~MainWindow()
{

    qDebug()<<"destroying mainwindow instance";
    delete TCPconnection;
    delete centralWidget;
    delete JSHandler;
    delete GUI;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{



    if(event->key()== Qt::Key_L){                                       //length measuring of task 3
        GUI->startLengthMeasuring();
    }
    else if(event->key()== Qt::Key_T){                                  //get temperature from pi & display it, or hide it if it is already being displayed
        emit messagePi("Temp");
        GUI->showOrHideTempLabel();
    }
    else if(event->key()== Qt::Key_F){                                  //full screen or normal screen for endoscope camera display
        emit endoToggleFullScreen();

    }
    else if(event->key()== Qt::Key_P){                                  //full screen or normal screen for endoscope camera display
        GUI->pause_play();

    }
    else if(event->key()== Qt::Key_R){                                  //full screen or normal screen for endoscope camera display
        GUI->restartTimer();

    }
//    else if(event->key()== Qt::Key_Space){                              //show or hide endoscope camera
//        qDebug()<<"key space pressed";
//        emit showOrHideEndoscopeCamera();
//    }
    else if(event->key()== Qt::Key_Minus){                                  //full screen or normal screen for endoscope camera display
        emit camerasSwitched();
    }
    qDebug()<<"Keyboard event detected";

}

void MainWindow::toggleFullScreen()
{
    this->isFullScreen() ? this->showNormal() : this->setWindowState(Qt::WindowFullScreen);
}

void MainWindow::delayMicroCamDisplay()
{
    qDebug()<<"starting delay of micro cam";
    if (GUI->isEndoscopeWidgetHidden()){
        emit messagePi("startMicro");
        microDisplayDelayTimer->setInterval(microCameraStartDelay);
        microDisplayDelayTimer->start();
    }
    else {
        emit messagePi("stopMicro");
        microDisplayDelayTimer->setInterval(10);
        microDisplayDelayTimer->start();
    }
}

void MainWindow::signalsHandler()
{
    connect(JSHandler,SIGNAL(sendToPi(QString)),TCPconnection,SLOT(sendMessage(QString)));
    connect(JSHandler,SIGNAL(guiChange(QString)),GUI,SLOT(changeInGUI(QString)));
    connect(JSHandler,SIGNAL(sendZDirection(QString)),GUI,SLOT(updateZdirection(QString)));
    connect(TCPconnection,SIGNAL(receivedmsg(QString)),GUI,SLOT(receiveFromPi(QString)));
    connect(GUI,SIGNAL(guiSizeChange()),this,SLOT(toggleFullScreen()));
    connect(GUI,SIGNAL(joystickForwardDirection(int)),JSHandler,SLOT(updateCamOnFocus(int)));
    connect(JSHandler,SIGNAL(showOrHideEndoscopeCamera()),this,SLOT(delayMicroCamDisplay()));
    connect(this,SIGNAL(messagePi(QString)),TCPconnection,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(endoToggleFullScreen()),GUI,SLOT(toggleEndoFullScreen()));
    connect(this,SIGNAL(camerasSwitched()),JSHandler,SLOT(correctCamerasSwitching()));
    connect(microDisplayDelayTimer,SIGNAL(timeout()),GUI,SLOT(showOrHideEndoscopeCamera()));
    connect(microDisplayDelayTimer,SIGNAL(timeout()),microDisplayDelayTimer,SLOT(stop()));


//    connect(this,SIGNAL(showOrHideEndoscopeCamera()),GUI,SLOT(showOrHideEndoscopeCamera()));
}






