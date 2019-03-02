#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    server=new TCPServer("1.1.1.1",9005);

//    server=new TCPServer("127.0.0.1",9000);
    handler = new Joystick_Handler();
    connect(handler,SIGNAL(sendToPi(QString)),server,SLOT(sendMessage(QString)));
    centralWidget=new QWidget();
    centralWidget->show();
    centralWidget->setWindowTitle("Stream");
    GUI=new gui(centralWidget);
    connect(handler,SIGNAL(sendToGUI(QString)),GUI,SLOT(changeInGUI(QString)));
    connect(server,SIGNAL(receivedmsg(QString)),GUI,SLOT(updateSensorLabel(QString)));
    createSettingsHandler();
}
QGridLayout *MainWindow::getLayout()
{
    return GUI->getLayout();
}

//void MainWindow::getCam(gstream *camera,uint8_t cameraNum)
//{
//    GUI->getCam(camera,cameraNum);
//}


void MainWindow::setCam(gstreamer *camera,uint8_t cameraNum)
{
    GUI->setCam(camera,cameraNum);
}


MainWindow::~MainWindow()
{

    qDebug()<<"destroying mainwindow instance";
    delete server;
    delete centralWidget;
    delete handler;
    delete GUI;
    delete butConfig;
    delete settingsHandler;


}

void MainWindow::createSettingsHandler()
{

    settingsHandler=new newSettingsHandler();
    connect(settingsHandler,SIGNAL(guiSettings(QString)),GUI,SLOT(changeInButtonsConfiguration(QString)));
    connect(settingsHandler,SIGNAL(piSettings(QString)),handler,SLOT(changeInButtonsConfiguration(QString)));
    connect(GUI,SIGNAL(show_hideButConfig()),settingsHandler,SLOT(show_hideButConfig()));
    connect(GUI,SIGNAL(setFullScreen()),this,SLOT(toggleFullScreen()));

}

void MainWindow::toggleFullScreen()
{
    centralWidget->isFullScreen() ? centralWidget->showNormal() : centralWidget->setWindowState(Qt::WindowFullScreen);
}






