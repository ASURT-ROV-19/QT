#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
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
    GUI=new gui(centralWidget);
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

    if(event->key()== Qt::Key_W){
        micro=1;
        emit messagePi("Micro_ROV "+QString::number(micro));
    }

    else if(event->key()== Qt::Key_S){
        micro=0;
        emit messagePi("Micro_ROV "+QString::number(micro));
    }

    else if(event->key()== Qt::Key_L){      //length measuring of task 3
        GUI->startLengthMeasuring();
    }
    else if(event->key()== Qt::Key_T){      //get water temperature from pi & display it, or hide it if it is already being displayed
        emit messagePi("Temp");
        GUI->showOrHideTempLabel();
    }

    else if(event->key()== Qt::Key_Space){      //show or hide endoscope camera
        qDebug()<<"key space pressed";
        emit showOrHideEndoscopeCamera();
    }

    else if(event->key()== Qt::Key_F){      //full screen or normal screen for endoscope camera display
        emit endoToggleFullScreen();

    }
    else if(event->key()== Qt::Key_Right){      //rotate micro_rov's servo in a direction
        pulley==-1 ? pulley=0 : pulley =1;
        emit messagePi("Pulley "+QString::number(pulley));

    }
    else if(event->key()== Qt::Key_Left){       //rotate micro_rov's servo in opposite direction
        pulley==1 ? pulley=0 : pulley =-1;
        emit messagePi("Pulley "+QString::number(pulley));

    }

    qDebug()<<"Keyboard event detected";

}

void MainWindow::toggleFullScreen()
{
    centralWidget->isFullScreen() ? centralWidget->showNormal() : centralWidget->setWindowState(Qt::WindowFullScreen);
}

void MainWindow::signalsHandler()
{
    connect(JSHandler,SIGNAL(sendToPi(QString)),TCPconnection,SLOT(sendMessage(QString)));
    connect(JSHandler,SIGNAL(guiChange(QString)),GUI,SLOT(changeInGUI(QString)));
    connect(TCPconnection,SIGNAL(receivedmsg(QString)),GUI,SLOT(receiveFromPi(QString)));
    connect(GUI,SIGNAL(guiSizeChange()),this,SLOT(toggleFullScreen()));
    connect(JSHandler,SIGNAL(sendZDirection(QString)),GUI,SLOT(updateZdirection(QString)));
    connect(this,SIGNAL(showOrHideEndoscopeCamera()),GUI,SLOT(showOrHideEndoscopeCamera()));
    connect(this,SIGNAL(messagePi(QString)),TCPconnection,SLOT(sendMessage(QString)));
    connect(this,SIGNAL(endoToggleFullScreen()),GUI,SLOT(toggleEndoFullScreen()));

}






