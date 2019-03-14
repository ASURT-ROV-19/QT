#ifndef GSTREAMER_H
#define GSTREAMER_H
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
#include <Qt5GStreamer/QGst/Ui/VideoWidget>
#include <QGraphicsView>
#include <Qt5GStreamer/QGst/Element>
#include <Qt5GStreamer/QGst/ElementFactory>
#include <Qt5GStreamer/QGst/Pipeline>
#include <Qt5GStreamer/QGst/Parse>
#include <Qt5GStreamer/QGst/Init>
#include <Qt5GStreamer/QGst/Bin>
#include <Qt5GStreamer/QGst/VideoOverlay>
#include <gst/video/video-overlay-composition.h>

//#include <QGst/Pipeline>


class gstreamer /*: public QGst::Ui::VideoWidget*/
{

public:
    gstreamer(int port);
    gstreamer(int port,int portToStreamTo);
    ~gstreamer();
    void autoSetPipeline();
    void setRenderingWindows();
//    QWidget * getRenderingWindow();
//    QVideoWidget * getRenderingVideoWindow();
    QGst::Ui::VideoWidget * getRenderingVideoWindow();
//    QGst::VideoOverlay
    QGraphicsView * getView();
public slots:
    void play_pause();
    void screenShot();

private:

//    QGst::Pipeline pipe;
    QGst::ElementPtr sink2,source;
    QGst::PipelinePtr pipe2;
    QGst::BinPtr runBin;
    GstElement *pipeline ,* sink;
    QWidget * window;
//    QVideoWidget * videowindow;
    QGst::Ui::VideoWidget * videowindow;
    uint8_t state=0;
    int PORT,portToStreamTo;
    std::string pipeline_description;
    QString desc;
};

#endif
