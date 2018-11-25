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

class gstream : public QObject
{
    Q_OBJECT
public:
    gstream(QWidget * parent,QGridLayout * layout);
    gstream(int port);
    gstream();
    ~gstream();
    int setPipeline();
    void autoSetPipeline();
    void setRenderingWindows();
    QWidget * getRenderingWindow();
    void manuallySetPipeline(std::string describtion);
    std::string getDescribtion();


public slots:
    void play_pause();
    void quitProgram();
    int linkElements();

private:
    GstElement *pipeline ,*source  ,*buffer,*depay,*decompressor,*convert,* sink;
    GstElement *capsfilter;
    GMainLoop *mainLoop;
    QWidget * window;
    uint8_t state=0;
    GstCaps * caps;
    uint8_t windowSelector=0;
    QGridLayout * GUILayOut;
    int PORT;
    GstSample * screenshot;
    std::string pipeline_description;

};

//#endif // GSTREAM_H
