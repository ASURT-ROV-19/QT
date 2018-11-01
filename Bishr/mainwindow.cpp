

#include "mainwindow.h"
#include "ui_mainwindow.h"

//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow)
//{

//    ui->setupUi(this);
//        this->setGeometry(200,200,800,600);
//        centralWidget=new QWidget(this);
////        centralWidget->setGeometry(0,0,600,500);
//        centralWidget->show();
//        this->show();
//        verLay=new QVBoxLayout();
//        centralWidget->setWindowTitle("Camera 1");
//        this->setCentralWidget(centralWidget);
////        this->set
//        this->setWindowTitle("sgsgafdgahaagb");
//        GUI=new gui(centralWidget);
//}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
        this->setGeometry(200,200,800,600);
        centralWidget=new QWidget();
        centralWidget->setGeometry(0,0,1280,960);
        centralWidget->show();
//        this->show();
//        verLay=new QVBoxLayout();
        centralWidget->setWindowTitle("Camera 1");
//        this->setCentralWidget(centralWidget);
//        this->set
        this->setWindowTitle("sgsgafdgahaagb");
        GUI=new gui(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}




