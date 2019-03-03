#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
int main(int argc, char *argv[])
{

    QApplication * a =new QApplication(argc, argv);
    MainWindow w;
    gstreamer camera22(5022);
    w.setDisplayWindow(camera22.getRenderingVideoWindow(),1);
    gstreamer camera21(10000);
    w.setDisplayWindow(camera21.getRenderingVideoWindow(),2);
    camera22.autoSetPipeline();
    camera21.autoSetPipeline();
    return a->exec();

}




//TODO::

/*
1-RECEIVE DATA FROM PI                  (((((((((****************************BECOMING CRITICAL*****************************)))))))))))),should be done by monday and tested by tuesday
2-PREPARE HOW DATA WILL BE DISPLAYED
3-expand buttons configuration in include Pi buttons too
*/
