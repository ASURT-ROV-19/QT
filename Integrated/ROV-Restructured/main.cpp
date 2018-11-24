#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication * a =new QApplication(argc, argv);
    MainWindow w;
    gstream camera2(10000);
    w.getCam(&camera2,2);
    gstream camera(5022);
    w.getCam(&camera,1);
//    camera.setPipeline();

//    w.addRedneringWindow(camera.getRenderingWindow(),0,0,1,1,1);
    camera.autoSetPipeline();
    camera.play_pause();
    camera2.autoSetPipeline();
    camera2.play_pause();

    return a->exec();
}


/*
  CURRENT PROBLEM IS IN TOGGLING BETWEEN CAMERAS , WHAT HAPPENS IS THAT WE ADD A NULLED WINDOW TO THE LAYOUT SO PROG CRASHES
  I SHALL FIGURE OUT SOMEHOW TO CHECK WHETHER THE WIDGET IS YET CREATED OR NOT
*/


/*
-message format
-last year's code for streaming
-buttons different settings
-use jpeg
-
*/
