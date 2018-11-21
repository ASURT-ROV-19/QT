#include "mainwindow.h"
#include <QApplication>
#include <gstreamer.h>

int main(int argc, char *argv[])
{
    QApplication * a =new QApplication(argc, argv);
    MainWindow w(a);
//    w.getApp(a);
//    w.show();
    gst_init(&argc,&argv);
//    return a->exec();
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
