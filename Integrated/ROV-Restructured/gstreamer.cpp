#include "gstreamer.h"


gstreamer::gstreamer(int port)
{
//    view=new QGraphicsView();
//    view->show();


//creating elements
    videowindow=new QGst::Ui::VideoWidget();
//    window=new QWidget();
//    videowindow->setAttribute(Qt::WA_TranslucentBackground);
//    videowindow->setStyleSheet("background:transparent;");
    videowindow->setStyleSheet("background-color:green;");
    videowindow->show();
//    this->hide();
//    window->show();
//    window->setWindowTitle("Gstreamer window");
    videowindow->setWindowTitle("Gstreamer videowindow");
    //    window->setStyleSheet("background:transparent;");
    PORT=port;
    QGst::init(0,0);
//    gst_init(0,0);
    pipeline = gst_pipeline_new ("xvoverlay");

}


void gstreamer::setRenderingWindows()
{

//    WId xwinid = videowindow->winId();
//    WId xwinid = view->winId();
    QApplication::sync();


    sink2=QGst::ElementFactory::make("qwidget5videosink");

//    sink2=QGst::ElementFactory::make("xvimagesink");
//    sink2->setProperty("autopaint-colorkey",false);
//    g_object_set(sink2, "autopaint-colorkey", FALSE,
//                 "colorkey", 0x080810, NULL);

sink2->setProperty("name","sink");
//    setVideoSink(sink2);
    videowindow->setVideoSink(sink2);
    pipe2=QGst::Pipeline::create();
    pipe2->add(source);
    pipe2->add(sink2);
    source->link(sink2);
    sink2->setProperty("force-aspect-ratio",false);
    sink2->setProperty("sync",false);
//    sink2->setProperty("enable-last-sample",true);
    if (!pipe2.isNull())
        pipe2->setState(QGst::StatePlaying);

//    sink2->setProperty("widget",window);
//    sink2->setProperty("display",&xwinid);


    //    sink=gst_bin_get_by_name(GST_BIN(pipeline),"sink");
//    videowindow->setUpdatesEnabled(true);
//    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (&sink2), xwinid);
//    gst_video_overlay_set_property(GST_OBJECT(sink),)
    //    g_object_set(sink,"autopaint-colorkey",false,NULL);
}


QGst::Ui::VideoWidget * gstreamer::getRenderingVideoWindow()
{
//    videowindow->show();
    return videowindow;
}

QGraphicsView *gstreamer::getView()
{
    return view;
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


gstreamer::~gstreamer()
{

    gst_object_unref(pipeline);
    gst_object_unref(sink2);
}

void gstreamer::autoSetPipeline()
{

// H264 compressing pipeline (sent data is initially key frame and all after that are changes in frame)
//    pipeline_description="udpsrc port="+QString::number(PORT).toStdString()+" ! application/x-rtp,encoding-name=H264 ! rtpjitterbuffer latency=0 ! rtph264depay ! avdec_h264 ! videoconvert ! xvimagesink name=sink  force-aspect-ratio=false";

// JPEG compressing pipeline (JPEG is frame by frame , requiring larger bandwidth but less delay )
    pipeline_description="udpsrc port="+QString::number(PORT).toStdString()+" ! application/x-rtp,media=video,clock-rate=90000,encoding-name=JPEG,payload=26 ! rtpjpegdepay ! jpegdec ! vaapipostproc";
    desc=QString::fromStdString(pipeline_description);
    source=QGst::Bin::fromDescription(desc);

    //    pipeline=gst_parse_launch(pipeline_description.c_str(),NULL);
    setRenderingWindows();
    getRenderingVideoWindow();
}



/*xvimagesink name=sink force-aspect-ratio=false sync=false enable-last-sample=true*/

