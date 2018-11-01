#ifndef GSTREAM_H
#define GSTREAM_H
#include <QVBoxLayout>
#include <QObject>
#include <glib.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <QApplication>
#include <QTimer>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QHBoxLayout>
class gstream : public QObject
{
    Q_OBJECT
public:
    gstream(QWidget * parent);
    gstream(QWidget * parent,QVBoxLayout * layout);
    gstream(QVBoxLayout * layout,QWidget * parent);
    int action(QWidget * renderingWindow,QVBoxLayout * layout);
    QWidget * getStream();
    QWidget * window2 ,* window;
    QWidget * getRenderingWindow();

private:
    GstElement *pipeline ,*source , *tee ,* queue1 ,* queue2,*buffer,*depay,*decompressor,*convert,* sink, *sink2;
    GstElement *source2 ,*buffer2,*depay2,*decompressor2,*convert2;

    GstElement * sinkForWindow2,*pipeline2 ;
//    GstElement * source
    QVBoxLayout * verLay;
    QPushButton * button;
    GstCaps * caps;
    QSpacerItem * vSpacer;
    QWidget * motherWidget;
    QHBoxLayout * horLay;
};

#endif // GSTREAM_H
