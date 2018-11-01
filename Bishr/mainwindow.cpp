

#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
        this->setGeometry(200,200,800,600);
        centralWidget=new QWidget();
        centralWidget->setGeometry(0,0,1280,960);
        centralWidget->show();
        centralWidget->setWindowTitle("Stream");
        GUI=new gui(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}




