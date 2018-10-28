#include "gstream.h"


gstream::gstream(QWidget *parent)
{
    verLay=new QVBoxLayout ();
    window=parent;
//    window=new QWidget(parent);
//    window->setGeometry(50,50,800,600);
//    window->show();
//    window->setLayout(verLay);
//    button=new QPushButton("USELESSSSS",parent);
//    verLay->addWidget(button);
    action(parent);
}


int gstream::action(QWidget * renderingWindow)
{

    if (!g_thread_supported ())
      g_thread_init (NULL);

    gst_init (0, 0);
    int x=0;
    char * y= NULL;
    QApplication app(x, &y);
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit ()));

    // prepare the pipeline

    pipeline = gst_pipeline_new ("xvoverlay");
//    pipeline = gst_parse_launch ("udpsrc port=5022 ! application/x-rtp,encoding-name=H264 ! rtpjitterbuffer ! rtph264depay ! avdec_h264 ! videoconvert ! ximagesink name=sink", NULL);
/*
      line 38 alone can do for splitting streaming into two directions , just uncomment it , uncomment line 126 &
      comment every thing else between the two lines , if you do so , you can remove most GstElements in the header file
*/
//    pipeline = gst_parse_launch ("udpsrc port=5022 ! application/x-rtp,encoding-name=H264 ! tee name=t ! queue ! udpsink port=10000 t. ! queue ! rtpjitterbuffer ! rtph264depay ! avdec_h264 ! videoconvert ! ximagesink name=sink", NULL);

//    pipeline = gst_parse_launch ("udpsrc port=5000 ! application/x-rtp,encoding-name=H264 ! rtpjitterbuffer ! rtph264depay ! avdec_h264 ! videoconvert ! ximagesink name=sink", NULL);
//    pipeline = gst_parse_launch ("v4l2src device='/dev/video0' ! video/x-raw,width=320,height=240 ! videoconvert ! x264enc tune=zerolatency ! rtph264pay ! udpsink host='bta3 el computer' port=5022"
//                                 ,NULL);
    // prepare the ui
//    window->resize(800 , 600);
//    window->show();


    source= gst_element_factory_make("udpsrc","source");
    buffer=gst_element_factory_make("rtpjitterbuffer","buffer");
    depay=gst_element_factory_make("rtph264depay","depay");
    decompressor=gst_element_factory_make("avdec_h264","deco");
    convert=gst_element_factory_make("videoconvert","converter");
    sink=gst_element_factory_make("ximagesink","sink");
    tee=gst_element_factory_make("tee","t1");
    queue1=gst_element_factory_make("queue","queue1");
    queue2=gst_element_factory_make("queue","queue2");
    sink2=gst_element_factory_make("udpsink","sink2");

    if (!pipeline || !source || !tee || !queue1 || !queue2 || !sink || !depay || !buffer || !convert || !decompressor) {
       g_printerr ("Not all elements could be created.\n");
       return -1;
     }
    caps= gst_caps_new_simple("application/x-rtp","media", G_TYPE_STRING, "video","encoding-name", G_TYPE_STRING,"H264",NULL);
    g_object_set(source,"port",5022,nullptr);
    g_object_set(source,"caps",caps, nullptr);
    g_object_set(buffer,"latency",0, nullptr);
    g_object_set(sink2,"port",10000,NULL);
    gst_caps_unref(caps);


    gst_bin_add_many (GST_BIN (pipeline), source, tee, queue1 , queue2, sink2, buffer,depay,decompressor,convert , sink, NULL);



        if (gst_element_link_many (buffer,depay,decompressor,convert , sink) != TRUE) {
          g_printerr ("Elements could not be linked.\n");
          gst_object_unref (pipeline);
          gst_object_unref (decompressor);
          gst_object_unref (depay);
          gst_object_unref (buffer);
//          gst_object_unref (caps);
          gst_object_unref (sink);
//          gst_object_unref (filter);
          gst_object_unref (convert);
          gst_object_unref (source);

          return -1;
      }else if (!gst_element_link(queue1,buffer)){
          g_printerr("Error at linking queue1 and buffer");
            return -1;
      }
        GstPad *teeDisplayPad = gst_element_get_request_pad(tee, "src_%u");
        GstPad *queueDisplayPad = gst_element_get_static_pad(queue1, "sink");

        GstPad *teeRecordPad = gst_element_get_request_pad(tee, "src_%u");
        GstPad *queueRecordPad = gst_element_get_static_pad(queue2, "sink");

        if(gst_pad_link(teeDisplayPad, queueDisplayPad) != GST_PAD_LINK_OK){
            g_print("Unable to link tee and queue1");
        }

        if(gst_pad_link(teeRecordPad, queueRecordPad) != GST_PAD_LINK_OK){
            g_print("Unable to link tee and queue2");
            return -1;
        }
        if (!gst_element_link(queue2,sink2)){
            g_print("Unable to link queue2 and sink2");
            return -1;
        }

        //gst_object_unref(teeDisplayPad);
        gst_object_unref(queueDisplayPad);
        //gst_object_unref(teeRecordPad);
        gst_object_unref(queueRecordPad);

      if (!gst_element_link(source,tee)){
          g_printerr("Error at linking source and buffer");
          gst_object_unref (pipeline);
          gst_object_unref (decompressor);
          gst_object_unref (depay);
          gst_object_unref (buffer);
//          gst_object_unref (caps);
          gst_object_unref (sink);
//          gst_object_unref (filter);
          gst_object_unref (convert);
          gst_object_unref (source);
          return -1;
      }
//    WId xwinid = window->winId();
      WId xwinid = window->winId();
//    sink=gst_bin_get_by_name(GST_BIN(pipeline),"sink");
    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sink), xwinid);

    /**********************************************************************************************/
//    renderingWindow->resize(800 , 600);
//    renderingWindow->show();
//    WId xwinid = renderingWindow->winId();
//    sink=gst_bin_get_by_name(GST_BIN(pipeline),"sink");
//    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sink), xwinid);

    /**********************************************************************************************/
    // run the pipeline

    GstStateChangeReturn sret = gst_element_set_state (pipeline,
        GST_STATE_PLAYING);

    if (sret == GST_STATE_CHANGE_FAILURE) {
      gst_element_set_state (pipeline, GST_STATE_NULL);
      gst_object_unref (pipeline);
      gst_object_unref (decompressor);
      gst_object_unref (depay);
      gst_object_unref (buffer);
      gst_object_unref (sink);
      gst_object_unref (sink2);
      gst_object_unref (tee);
      gst_object_unref (queue1);
      gst_object_unref (queue2);
      gst_object_unref (convert);
      gst_object_unref (source);
      // Exit application
      QTimer::singleShot(0, QApplication::activeWindow(), SLOT(quit()));
    }

    int ret = app.exec();

    window->hide();
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
    gst_object_unref (decompressor);
    gst_object_unref (depay);
    gst_object_unref (buffer);
    gst_object_unref (sink);
    gst_object_unref (sink2);
    gst_object_unref (tee);
    gst_object_unref (queue1);
    gst_object_unref (queue2);
    gst_object_unref (convert);
    gst_object_unref (source);


    return ret;

}

QWidget *gstream::getStream()
{
    return window;
}

QWidget * gstream::getRenderingWindow()
{
    return window;
}
