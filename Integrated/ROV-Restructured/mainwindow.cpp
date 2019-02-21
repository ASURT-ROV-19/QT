#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    server=new TCPServer("1.1.1.1",9005);
//    server=new TCPServer("127.0.0.1",9005);
    handler = new Joystick_Handler();
    //ui->setupUi(this);
    connect(handler,SIGNAL(sendToPi(QString)),server,SLOT(sendMessage(QString)));
    centralWidget=new QWidget();
//    centralWidget->setWindowState(Qt::WindowFullScreen);
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


void MainWindow::getCam(gstreamer *camera,uint8_t cameraNum)
{
    GUI->getCam(camera,cameraNum);
}


MainWindow::~MainWindow()
{
    //    delete ui;
}

void MainWindow::createSettingsHandler()
{

    settingsHandler=new newSettingsHandler();
    connect(settingsHandler,SIGNAL(guiSettings(QString)),GUI,SLOT(changeInButtonsConfiguration(QString)));
    connect(settingsHandler,SIGNAL(piSettings(QString)),handler,SLOT(changeInButtonsConfiguration(QString)));
    connect(GUI,SIGNAL(show_hideButConfig()),settingsHandler,SLOT(show_hideButConfig()));

    //    void piSettings(QString newSettings);
//    void guiSettings(QString newSettings);

}






