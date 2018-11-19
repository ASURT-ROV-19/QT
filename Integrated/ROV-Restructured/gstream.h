//#ifndef GSTREAM_H
//#define GSTREAM_H
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
class gstream : public QObject
{
    Q_OBJECT
public:
    gstream(QWidget * parent,QGridLayout * layout);
    int setPipelines();
    void setRenderingWindows();


public slots:
    void play_pause();
    void quitProgram();

private:
    GstElement *pipeline ,*source , *tee ,* queue1 ,* queue2,*buffer,*depay,*decompressor,*convert,* sink, *sink2;
    GstElement *source2 ,*buffer2,*depay2,*decompressor2,*convert2,*scalingConvert,*scaler,*capsfilter;
    GMainLoop *mainLoop;
    QWidget * window2 ,* window;
    GstElement * sinkForWindow2,*pipeline2 ;
    uint8_t state=0;
    GstCaps * caps,*scalingCaps;
    int windowSelector=0;
    QGridLayout * GUILayOut;

};

//#endif // GSTREAM_H
