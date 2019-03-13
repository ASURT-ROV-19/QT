#include "gstreamer.h"


gstreamer::gstreamer(int port)
{
//    view=new QGraphicsView();
//    view->show();


//creating elements
    videowindow=new QGst::Ui::VideoWidget();
    videowindow->setStyleSheet("background-color:green;");
    videowindow->show();
    videowindow->setWindowTitle("Gstreamer videowindow");
    PORT=port;
    QGst::init(0,0);
    pipeline = gst_pipeline_new ("xvoverlay");

}


void gstreamer::setRenderingWindows()
{
    QApplication::sync();
    sink2=QGst::ElementFactory::make("qwidget5videosink");
    sink2->setProperty("name","sink");
    videowindow->setVideoSink(sink2);
    pipe2=QGst::Pipeline::create();
    pipe2->add(source);
    pipe2->add(sink2);
    source->link(sink2);
    sink2->setProperty("force-aspect-ratio",false);
    sink2->setProperty("sync",false);
    if (!pipe2.isNull())
        pipe2->setState(QGst::StatePlaying);

}


QGst::Ui::VideoWidget * gstreamer::getRenderingVideoWindow()
{
    return videowindow;
}




void gstreamer::play_pause()
{
    if (state==0){
        gst_element_set_state(pipeline,GST_STATE_PLAYING);
        state=1;
    }
    else if (state==1){
        gst_element_set_state(pipeline,GST_STATE_PAUSED);
        state=0;
    }
}

void gstreamer::screenShot()
{

}


gstreamer::~gstreamer()
{
    qDebug()<<"destroying countDown instance";
    gst_object_unref(sink2);
    gst_object_unref(source);
    delete [] window;
    gst_object_unref(videowindow);

}

void gstreamer::autoSetPipeline()
{
// JPEG compressing pipeline (JPEG is frame by frame , requiring larger bandwidth but less delay )
//                                                               udpsrc port=5022 ! application/x-rtp,media=video,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! vaapipostproc
        pipeline_description="udpsrc port="+QString::number(PORT).toStdString()+" ! application/x-rtp,media=video,clock-rate=90000,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! vaapipostproc";
//        pipeline_description="udpsrc port="+QString::number(PORT).toStdString()+" ! application/x-rtp,media=video,clock-rate=90000,encoding-name=JPEG,payload=26 ! rtpjpegdepay ! vaapijpegdec ! videoconvert";
    desc=QString::fromStdString(pipeline_description);
    source=QGst::Bin::fromDescription(desc);

    //    pipeline=gst_parse_launch(pipeline_description.c_str(),NULL);
    setRenderingWindows();
    getRenderingVideoWindow();
}



