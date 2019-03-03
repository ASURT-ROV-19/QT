#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
//    TCPconnection=new TCPConnection("1.1.1.1",9005);

    TCPconnection=new TCPConnection("127.0.0.1",9000);
    JSHandler = new Joystick_Handler();
    connect(JSHandler,SIGNAL(sendToPi(QString)),TCPconnection,SLOT(sendMessage(QString)));
    centralWidget=new QWidget();
    centralWidget->show();
    centralWidget->setWindowTitle("Stream");
    GUI=new gui(centralWidget);
    connect(JSHandler,SIGNAL(guiChange(QString)),GUI,SLOT(changeInGUI(QString)));
    connect(TCPconnection,SIGNAL(receivedmsg(QString)),GUI,SLOT(updateSensorLabel(QString)));
    connect(GUI,SIGNAL(guiSizeChange()),this,SLOT(toggleFullScreen()));
}



void MainWindow::setDisplayWindow(QGst::Ui::VideoWidget * displayWindow,uint8_t cameraNum)
{
    GUI->setDisplayWindow(displayWindow,cameraNum);
}


MainWindow::~MainWindow()
{

    qDebug()<<"destroying mainwindow instance";
    delete TCPconnection;
    delete centralWidget;
    delete JSHandler;
    delete GUI;

}

void MainWindow::toggleFullScreen()
{
    centralWidget->isFullScreen() ? centralWidget->showNormal() : centralWidget->setWindowState(Qt::WindowFullScreen);
}






