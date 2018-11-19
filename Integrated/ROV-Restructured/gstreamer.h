#ifndef GSTREAMER_H
#define GSTREAMER_H
#include <QObject>
#include <glib.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <QApplication>
#include <QTimer>
#include <QWidget>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QApplication>
class gstreamer : public QObject
{
    Q_OBJECT
public:
    gstreamer(QWidget * parent,QVBoxLayout * layout);

    gstreamer(QWidget * parent,QGridLayout * layout);
    int action(QApplication * myApp);
    QWidget * getRenderingWindow(int windowNumber);
    void setWindowsSize();
    int setPipelines();
    void setRenderingWindows();
    void changeDisplaySize(int height,int width);
    void autoSetPipelines();
//    void setReady();
//    void stop();
    ~gstreamer();
public slots:
    void play_pause();
    void quitProgram();
private:
    QWidget * window2 ,* window;
    GstElement *pipeline ,*source , *tee ,* queue1 ,* queue2,*buffer,*depay,*decompressor,*convert,* sink, *sink2;
    GstElement *source2 ,*buffer2,*depay2,*decompressor2,*convert2,*scalingConvert,*scaler,*capsfilter;
//    GstElement * sourcePipeline;
    GMainLoop *mainLoop;
    int state=0;
    GstElement * sinkForWindow2,*pipeline2 ;

    GstCaps * caps,*scalingCaps;
    QSpacerItem * vSpacer;
    QWidget * motherWidget;
    QHBoxLayout * horLay;
    int windowSelector=0;
    QGridLayout * GUILayOut;
};

#endif // GSTREAM_H
