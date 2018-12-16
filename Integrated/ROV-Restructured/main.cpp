#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication * a =new QApplication(argc, argv);
    MainWindow w;
    gstream camera2(5022);
    w.getCam(&camera2,1);
    gstream camera(8765);
    w.getCam(&camera,2);

    camera.autoSetPipeline();
    camera2.autoSetPipeline();

    camera.play_pause();
    camera2.play_pause();

    return a->exec();
}


