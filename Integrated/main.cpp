#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication * a =new QApplication(argc, argv);
    MainWindow * mainWindow = nullptr;
    gstreamer * camera22 = nullptr;
    gstreamer * camera21=nullptr;
    qDebug()<<"argc is "<<argc;
    for (int i=0;i<argc;i++)
        qDebug()<<"argv["<<i<<"]= "<<argv[i]<<endl;


    if (argc==3){
        mainWindow=new MainWindow(nullptr,QString::fromLocal8Bit(argv[1]),QString::fromLocal8Bit(argv[2]));
        camera22=new gstreamer(5022);
        camera21=new gstreamer(10000,5022);
    }
    else if (argc==2){
        mainWindow=new MainWindow();
        if (QString::fromLocal8Bit(argv[1])=="10000"){
            camera22=new gstreamer(5022);
            camera21=new gstreamer(10000,5022);
            qDebug()<<"streaming to port 5022 from port 10000";
        }
        else {
            camera22=new gstreamer(5022,10000);
            camera21=new gstreamer(10000);
        }
    }
    else if (argc==4){
        mainWindow=new MainWindow(nullptr,QString::fromLocal8Bit(argv[1]),QString::fromLocal8Bit(argv[2]));
        if (QString::fromLocal8Bit(argv[3])=="10000"){
            camera22=new gstreamer(5022);
            camera21=new gstreamer(10000,5022);
        }
        else {
            camera22=new gstreamer(5022,10000);
            camera21=new gstreamer(10000);
        }
    }
    else {
        mainWindow=new MainWindow();
        camera22=new gstreamer(5022,5000);
        camera21=new gstreamer(10000);
    }

    mainWindow->setDisplayWindow(camera22->getRenderingVideoWindow(),0);
    gstreamer endoscopeCamera(1234);
    mainWindow->setDisplayWindow(camera21->getRenderingVideoWindow(),1);
    camera22->autoSetPipeline();
    camera21->autoSetPipeline();
    endoscopeCamera.autoSetPipeline();
    mainWindow->setEndoscopeCamera(&endoscopeCamera);
    return a->exec();
    delete mainWindow;
    delete camera21;
    delete camera22;

}




//TODO::

/*
on how to handle new buttons configurations :
        simply , make the communication b/w the settings handler and the joystick handler , and no change is felt outside these two classes , if buttonA changes from value 0 to 1
        the change is handeled in the joystick handler , and when joystick button 1 is pressed , js handler still emits 0 , it did the mapping form 1 to zero based on the new
        settings , nobody else other than it feels the change .
*/


/*
buttons 7 & 9 in joystick are almost dead
buttons 10 & 11 to be used for magazine servo
buttons 6 to be used for fullscreening mainWindow or normal screening it
button 8 for PID
button 7 for toggling zMode
*/
