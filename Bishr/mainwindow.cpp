

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
/*
    ui->setupUi(this);
    controller=new joystick();
    piSock=new tcpsocket(this,8082);

//    ImageProcessingSock=new tcpsocket(this,12000);
    this->setGeometry(200,200,800,600);
    verLay=new QVBoxLayout();
    centralWidget=new QWidget;
    centralWidget->setLayout(verLay);
//    stream=new streamer(centralWidget);
//    verLay->addWidget(stream->getVideoWidget());          //for local video view
//    verLay->addWidget(stream->getViewFinder());         //for webCam view
//    verLay->addItem(stream->getPipeline());
    streamingWidget=new QWidget();
//    streamingWidget->show();
    verLay->addWidget(streamingWidget);
    connect(controller ,SIGNAL(streamData(QString)),piSock,SLOT(setMessage(QString)));

    str=new gstream(streamingWidget);
    verLay->addWidget(str->getStream());
    verLay->setMargin(0);
    bttn1=new QPushButton(this);
    bttn1->setText("Useless");
    bttn1->setGeometry(50,50,100,100);
    verLay->addWidget(bttn1);
    this->setCentralWidget(centralWidget);
    this->show();
*/
    ui->setupUi(this);
        this->setGeometry(200,200,800,600);
        verLay=new QVBoxLayout();
        centralWidget=new QWidget;
//        centralWidget->setLayout(verLay);
        centralWidget->show();

        GUI=new gui(centralWidget);


        this->setCentralWidget(centralWidget);
//        this->setCentralWidget(centralWidget);
        this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}




