#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    joyS=new Joystick_Handler;
    server=new TCPServer("111.111.111.111",5000);
    countd= new Countdown(this);
    ui->setupUi(this);
    connect(joyS,SIGNAL(msgsent(string)),server,SLOT(sendmsg(string)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


