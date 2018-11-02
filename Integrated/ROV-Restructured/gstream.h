#ifndef GSTREAM_H
#define GSTREAM_H
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
class gstream : public QObject
{
    Q_OBJECT
public:
    gstream(QWidget * parent,QVBoxLayout * layout);
    int action(QLabel *timerLAbel);
    QWidget * window2 ,* window;
    QWidget * getRenderingWindow(int windowNumber);

private:
    GstElement *pipeline ,*source , *tee ,* queue1 ,* queue2,*buffer,*depay,*decompressor,*convert,* sink, *sink2;
    GstElement *source2 ,*buffer2,*depay2,*decompressor2,*convert2;
//    GstElement * sourcePipeline;

    GstElement * sinkForWindow2,*pipeline2 ;

    GstCaps * caps;
    QSpacerItem * vSpacer;
    QWidget * motherWidget;
    QHBoxLayout * horLay;
};

#endif // GSTREAM_H
