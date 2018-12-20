#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    joyS=new Joystick_Handler();
    server=new TCPServer("10.0.1.55",9005);
    //ui->setupUi(this);
    connect(joyS,SIGNAL(sendToServer(QString)),server,SLOT(sendMessage(QString)));
    centralWidget=new QWidget();
    centralWidget->setWindowState(Qt::WindowFullScreen);
    centralWidget->show();
    centralWidget->setWindowTitle("Stream");
    GUI=new gui(centralWidget);
    connect(joyS,SIGNAL(sendToGUI(QString)),GUI,SLOT(changeInGUI(QString)));

}

QGridLayout *MainWindow::getLayout()
{
    return GUI->getLayout();
}

void MainWindow::getCam(gstream *camera,uint8_t cameraNum)
{
    GUI->getCam(camera,cameraNum);
}

void MainWindow::getCam(gstreamer *camera,uint8_t cameraNum)
{
    GUI->getCam(camera,cameraNum);
}



MainWindow::~MainWindow()
{
//    delete ui;
}



