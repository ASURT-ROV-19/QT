#include "gstream.h"


gstream::gstream(int port)
{
    view=new QGraphicsView();
    view->show();


//creating elements
    videowindow=new QVideoWidget();
//    videowindow->setAttribute(Qt::WA_TranslucentBackground);
//    videowindow->setStyleSheet("background:transparent;");
//    videowindow->setStyleSheet("background-color:red;");
    //    window->setStyleSheet("background:transparent;");
    PORT=port;
    gst_init(0,0);
    pipeline = gst_pipeline_new ("xvoverlay");

}


void gstream::setRenderingWindows()
{
//    WId xwinid = videowindow->winId();
    WId xwinid = view->viewport()->effectiveWinId();
    QApplication::sync();
    sink=gst_bin_get_by_name(GST_BIN(pipeline),"sink");
    videowindow->setUpdatesEnabled(true);
    qDebug()<<"before xwinid in gstream";
    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sink), xwinid);
    qDebug()<<"after xwinid in gstream";
    //    gst_video_overlay_set_property(GST_OBJECT(sink),)
    //    g_object_set(sink,"autopaint-colorkey",false,NULL);
}


QVideoWidget *gstream::getRenderingVideoWindow()
{
    videowindow->show();
    return videowindow;
}

QGraphicsView *gstream::getView()
{
    return view;
}




void gstream::play_pause()
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


gstream::~gstream()
{

    gst_object_unref(pipeline);
    gst_object_unref(sink);
}

void gstream::autoSetPipeline()
{

// H264 compressing pipeline (sent data is initially key frame and all after that are changes in frame)
//    pipeline_description="udpsrc port="+QString::number(PORT).toStdString()+" ! application/x-rtp,encoding-name=H264 ! rtpjitterbuffer latency=0 ! rtph264depay ! avdec_h264 ! videoconvert ! xvimagesink name=sink  force-aspect-ratio=false";

// JPEG compressing pipeline (JPEG is frame by frame , requiring larger bandwidth but less delay )
    pipeline_description="udpsrc port="+QString::number(PORT).toStdString()+" ! application/x-rtp,media=video,clock-rate=90000,encoding-name=JPEG,payload=26 ! rtpjpegdepay ! jpegdec ! vaapipostproc ! xvimagesink name=sink force-aspect-ratio=false sync=false enable-last-sample=true";

    pipeline=gst_parse_launch(pipeline_description.c_str(),NULL);
    setRenderingWindows();
    getRenderingVideoWindow();
}
