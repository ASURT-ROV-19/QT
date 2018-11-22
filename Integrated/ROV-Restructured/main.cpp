#include "mainwindow.h"
#include <QApplication>
#include <gstream.h>

int main(int argc, char *argv[])
{
    QApplication * a =new QApplication(argc, argv);
    MainWindow w;

    gstream camera(5022,w.getLayout(),0,0,1,1);
//    gstream camera(5022);
//    camera.setPipeline();
    camera.autoSetPipeline();
    camera.play_pause();

//    w.addRedneringWindow(camera.getRenderingWindow(),0,0,6,6,1);
    return a->exec();
}


/*
    Next to do is to use grid layout instead of two layouts for the GUI
*/


/*
-message format
-last year's code for streaming
-buttons different settings
-use jpeg
-
*/
