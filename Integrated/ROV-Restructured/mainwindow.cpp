#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    joyS=new Joystick_Handler();
    server=new TCPServer("127.0.0.1",5000);
    ui->setupUi(this);
    connect(joyS,SIGNAL(sendToServer(QString)),server,SLOT(sendmsg(QString)));
    centralWidget=new QWidget();
    centralWidget->setGeometry(0,0,1280,960);
    centralWidget->show();
    centralWidget->setWindowTitle("Stream");
//    centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    GUI=new gui(centralWidget);
    connect(joyS,SIGNAL(sendToGUI(QString)),GUI,SLOT(changeInGUI(QString)));
}

QGridLayout *MainWindow::getLayout()
{
    return GUI->getLayout();
}

void MainWindow::addRedneringWindow(QWidget *window, uint8_t row, uint8_t col, uint8_t wid,uint8_t  hei, uint8_t windowNum)
{
    GUI->addWidgetToLayout(window,row,col,wid,hei,windowNum);
}


MainWindow::~MainWindow()
{
    delete ui;
}



