//#ifndef GSTREAM_H
//#define GSTREAM_H
#include <QObject>
#include <glib.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <QApplication>
#include <QTimer>
#include <QWidget>
#include <QGridLayout>
#include <QDebug>
class gstream : public QObject
{
    Q_OBJECT
public:
    gstream(int port);
    ~gstream();
//    int setPipeline();
    void autoSetPipeline();
    void setRenderingWindows();
    QWidget * getRenderingWindow();
//    std::string getDescribtion();


public slots:
    void play_pause();
//    void quitProgram();
//    int linkElements();

private:
    GstElement *pipeline ,* sink;//,*source  ,*buffer,*depay,*decompressor,*convert;
//    GMainLoop *mainLoop;
    QWidget * window;
    uint8_t state=0;
//    GstCaps * caps;
//    GstElement *capsfilter;
//    GstSample * screenshot;
    uint8_t windowSelector=0;
    QGridLayout * GUILayOut;
    int PORT;
    std::string pipeline_description;

};

//#endif // GSTREAM_H
