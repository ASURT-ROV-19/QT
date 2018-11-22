#include "gstream.h"


gstream::gstream(QWidget *parent, QGridLayout *layout)
{
    layout->addWidget(window,0,0);
}

gstream::gstream(int port)
{
    //creating elements
    window=new QWidget ();
//    layout->addWidget(window,r,c,w,h);
    window->setAttribute(Qt::WA_TranslucentBackground);
    window->setStyleSheet("background:transparent;");
    gst_init(0,0);
    pipeline = gst_pipeline_new ("xvoverlay");
    source= gst_element_factory_make("udpsrc","source");
    buffer=gst_element_factory_make("rtpjitterbuffer","buffer");
    depay=gst_element_factory_make("rtph264depay","depay");
    decompressor=gst_element_factory_make("avdec_h264","deco");
    convert=gst_element_factory_make("videoconvert","converter");
    sink=gst_element_factory_make("ximagesink","sink");
    g_object_set(source,"port",port,nullptr);



}

gstream::gstream(int port, QGridLayout *layout, uint r, uint c, uint w, uint h)
{
    //creating elements
    window=new QWidget ();
    layout->addWidget(window,r,c,w,h);
    window->setAttribute(Qt::WA_TranslucentBackground);
    window->setStyleSheet("background:transparent;");
    gst_init(0,0);
    pipeline = gst_pipeline_new ("xvoverlay");
    source= gst_element_factory_make("udpsrc","source");
    buffer=gst_element_factory_make("rtpjitterbuffer","buffer");
    depay=gst_element_factory_make("rtph264depay","depay");
    decompressor=gst_element_factory_make("avdec_h264","deco");
    convert=gst_element_factory_make("videoconvert","converter");
    sink=gst_element_factory_make("ximagesink","sink");
    g_object_set(source,"port",port,nullptr);

}

int gstream::setPipeline()
{


//checking whether all elements are created correctly or not


    if (!pipeline || !source || !sink || !depay || !buffer || !convert || !decompressor) {
       g_printerr ("Not all elements could be created.\n");
       return -1;
     }

    gst_bin_add_many(GST_BIN(pipeline),source,buffer,depay,decompressor,convert,sink,NULL);

//creating capabilities and setting them to suit pipeline's data
    caps= gst_caps_new_simple("application/x-rtp","media", G_TYPE_STRING, "video","encoding-name", G_TYPE_STRING,"H264",NULL);

//setting caps and properties of elements

    g_object_set(source,"caps",caps, nullptr);
    g_object_set(buffer,"latency",0, nullptr);




    setRenderingWindows();
    return linkElements();
}


void gstream::setRenderingWindows()
{
    WId xwinid = window->winId();
    sink=gst_bin_get_by_name(GST_BIN(pipeline),"sink");
    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sink), xwinid);

}

QWidget *gstream::getRenderingWindow()
{
    return window;
}


void gstream::play_pause()
{
    if (state==0){
        g_print("shall play\n");
        gst_element_set_state(pipeline,GST_STATE_PLAYING);
        state=1;
    }
    else if (state==1){
        g_print("shall pause\n");
        gst_element_set_state(pipeline,GST_STATE_PAUSED);
        state=0;
    }
}

void gstream::quitProgram()
{
    g_print("shall end loop\n");
}

int gstream::linkElements()
{
    if (!gst_element_link(source,buffer))
    {
        g_print("Couldn't link 1 \n");
        return -1;
    }
    if (!gst_element_link(buffer,depay))
    {
        g_print("Couldn't link 2 \n");
        return -1;
    }
    if (!gst_element_link(depay,decompressor))
    {
        g_print("Couldn't link 3 \n");
        return -1;
    }
    if (!gst_element_link(decompressor,convert))
    {
        g_print("Couldn't link 4 \n");
        return -1;
    }
    if (!gst_element_link(convert,sink))
    {
        g_print("Couldn't link 5 \n");
        return -1;
    }
}


gstream::~gstream()
{
//    pipeline ,*source  ,*buffer,*depay,*decompressor,*convert,* sink
    gst_object_unref(pipeline);
    gst_object_unref(sink);
    gst_object_unref(buffer);
    gst_object_unref(depay);
    gst_object_unref(decompressor);
    gst_object_unref(convert);
    gst_object_unref(sink);
}

void gstream::autoSetPipeline()
{
    pipeline=gst_parse_launch("udpsrc port=5022 ! application/x-rtp,encoding-name=H264 ! rtpjitterbuffer latency=0 ! rtph264depay ! avdec_h264 ! videoconvert ! ximagesink name=sink",NULL);
    setRenderingWindows();
}
