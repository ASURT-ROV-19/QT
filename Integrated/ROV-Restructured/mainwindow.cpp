#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

//    joyS=new Joystick_Handler();
//    server=new TCPServer("127.0.0.1",5000);
    ui->setupUi(this);
//    connect(joyS,SIGNAL(msgsent(string)),this,SLOT(sendToGUI(string)));
//    connect(joyS,SIGNAL(msgsent(string)),server,SLOT(sendmsg(string)));
//    connect(joyS,SIGNAL(msgsent(string)),server,SLOT(sendmsg(string)));
    centralWidget=new QWidget();
    centralWidget->setGeometry(0,0,1280,960);
    centralWidget->show();
    centralWidget->setWindowTitle("Stream");

//    centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    GUI=new gui(centralWidget);
}

MainWindow::MainWindow(QApplication * myApp) :
    ui(new Ui::MainWindow)
{

    joyS=new Joystick_Handler();
    server=new TCPServer("127.0.0.1",5000);
    ui->setupUi(this);
    connect(joyS,SIGNAL(msgsent(string)),this,SLOT(sendToGUI(string)));
    connect(joyS,SIGNAL(msgsent(string)),server,SLOT(sendmsg(string)));
    connect(joyS,SIGNAL(msgsent(string)),server,SLOT(sendmsg(string)));
    centralWidget=new QWidget();
    centralWidget->setGeometry(0,0,1280,960);
    centralWidget->show();
    centralWidget->setWindowTitle("Stream");
//    centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    GUI=new gui(centralWidget);
    connect(joyS,SIGNAL(timerPause_Play()),GUI,SLOT(pause_play_Timer()));
    GUI->startListening(myApp);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getApp(QApplication *application)
{
    QApplication * myApp=application;
}

void MainWindow::sendToGUI(string message)
{
    if (message=="1")
        qDebug()<<"In main window and shall send to gui";
        GUI->changeInGUI(QString::fromStdString(message));
}

