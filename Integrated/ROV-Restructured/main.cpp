#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication * a =new QApplication(argc, argv);
    MainWindow w;
//    gstream camera2(15000);
//    w.getCam(&camera2,1);
//    gstream camera(15001);
//    w.getCam(&camera,2);


//    camera.autoSetPipeline();
//    camera2.autoSetPipeline();
//    camera2.play_pause();
//    camera.play_pause();

//______________________________________________________________________

    gstreamer camera22(5022);
    w.getCam(&camera22,1);
    gstreamer camera21(10000);
    w.getCam(&camera21,2);

    camera22.autoSetPipeline();
    camera21.autoSetPipeline();
//    camera22.setWindowTitle("CAmera22");
//    camera22.hide();
//    camera21.setWindowTitle("CAmera21");
//    camera21.hide();
    camera22.play_pause();
    camera21.play_pause();

    return a->exec();
}


