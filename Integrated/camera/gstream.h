#ifndef GSTREAM_H
#define GSTREAM_H
#include <QObject>
#include <glib.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <QApplication>
#include <QTimer>
#include <QWidget>
#include <QGridLayout>
#include <QDebug>
#include <QVideoWidget>
#include <Qt5GStreamer/QGst/VideoOverlay>
#include <QGst/Ui/VideoWidget>
#include <QGraphicsView>
#include <QGst/Element>
#include <QGst/ElementFactory>
#include <QGst/Pipeline>


class gstream : public QGst::Ui::VideoWidget
{

public:
    gstream(int port);
    ~gstream();
    void autoSetPipeline();
    void setRenderingWindows();
//    QWidget * getRenderingWindow();
    QVideoWidget * getRenderingVideoWindow();
//    QGst::VideoOverlay
    QGraphicsView * getView();
public slots:
    void play_pause();

private:

    QGraphicsView * view;
//    QGst::Pipeline pipe;
//    QGst::ElementPtr sink2;

    GstElement *pipeline ,* sink;
//    QWidget * window;
    QVideoWidget * videowindow;
    uint8_t state=0;
    uint8_t windowSelector=0;
    QGridLayout * GUILayOut;
    int PORT;
    std::string pipeline_description;
};

#endif
