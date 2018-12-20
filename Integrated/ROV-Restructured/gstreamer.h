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
#include <QGst/Ui/VideoWidget>
#include <QGraphicsView>
#include <QGst/Element>
#include <QGst/ElementFactory>
#include <QGst/Pipeline>
#include <QGst/Parse>
#include <QGst/Init>
#include <QGst/Bin>
#include <QGst/VideoOverlay>
#include <gst/video/video-overlay-composition.h>

//#include <QGst/Pipeline>


class gstreamer /*: public QGst::Ui::VideoWidget*/
{

public:
    gstreamer(int port);
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

private:

    QGraphicsView * view;
//    QGst::Pipeline pipe;
    QGst::ElementPtr sink2,source;
    QGst::PipelinePtr pipe2;
    QGst::BinPtr runBin;
    GstElement *pipeline ,* sink;
    QWidget * window;
//    QVideoWidget * videowindow;
    QGst::Ui::VideoWidget * videowindow;
    uint8_t state=0;
    uint8_t windowSelector=0;
    QGridLayout * GUILayOut;
    int PORT;
    std::string pipeline_description;
    QString desc;
};

#endif
