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

class gstream : public QObject
{
    Q_OBJECT
public:
    gstream(QWidget * parent);
    int action(QWidget * renderingWindow);
    QWidget * getStream();
    QWidget * window;
    QWidget * getRenderingWindow();
private:
    GstElement *pipeline ,*source , *tee ,* queue1 ,* queue2,*buffer,*depay,*decompressor,*convert,* sink, *sink2;

//    GstElement * source
    QVBoxLayout * verLay;
    QPushButton * button;
    GstCaps * caps;

};

#endif // GSTREAM_H
