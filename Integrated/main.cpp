#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication * a =new QApplication(argc, argv);
    MainWindow w;
    gstreamer camera22(5022,5000);
    w.setDisplayWindow(camera22.getRenderingVideoWindow(),0);
    gstreamer camera21(10000);
    gstreamer endoscopeCamera(1234);
    w.setDisplayWindow(camera21.getRenderingVideoWindow(),1);
    camera22.autoSetPipeline();
    camera21.autoSetPipeline();
    endoscopeCamera.autoSetPipeline();
    w.setEndoscopeCamera(&endoscopeCamera);
    return a->exec();

}




//TODO::

/*
on how to handle new buttons configurations :
        simply , make the communication b/w the settings handler and the joystick handler , and no change is felt outside these two classes , if buttonA changes from value 0 to 1
        the change is handeled in the joystick handler , and when joystick button 1 is pressed , js handler still emits 0 , it did the mapping form 1 to zero based on the new
        settings , nobody else other than it feels the change .
*/
