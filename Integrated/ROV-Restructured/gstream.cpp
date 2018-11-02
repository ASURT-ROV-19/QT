
#include "gstream.h"



gstream::gstream(QWidget *parent, QVBoxLayout *layout)
{
    motherWidget=new QWidget(parent);
    window=new QWidget();
    window->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    window2=new QWidget();
    window2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    window->setStyleSheet("background-color: cyan");
    window2->setStyleSheet("background-color: cyan");
    //    window=parent;
    horLay=new QHBoxLayout();
    horLay->addWidget(window);
    motherWidget->setLayout(horLay);
//    window->setGeometry(0,0,500,500);
//    layout->addWidget(window);
    layout->addWidget(motherWidget);
    vSpacer=new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Expanding);
    horLay->addWidget(window2);
    horLay->addSpacerItem(vSpacer);
    layout->addSpacerItem(vSpacer);
}



int gstream::action(QLabel *timerLAbel)
{

    if (!g_thread_supported ())
      g_thread_init (NULL);

    gst_init (0, 0);
    int x =0;
    char * y= NULL;
    QApplication app(x, &y);
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit ()));

    // prepare the pipeline
/*
      line 38 alone can do for splitting streaming into two directions , just uncomment it , uncomment line 126 &
      comment every thing else between the two lines , if you do so , you can remove most GstElements in the header file
*/
//    pipeline = gst_parse_launch ("udpsrc port=5022 ! application/x-rtp,encoding-name=H264 ! tee name=t ! queue ! udpsink port=10000 t. ! queue ! rtpjitterbuffer ! rtph264depay ! avdec_h264 ! videoconvert ! ximagesink name=sink", NULL);

//    pipeline = gst_parse_launch ("udpsrc port=5000 ! application/x-rtp,encoding-name=H264 ! rtpjitterbuffer ! rtph264depay ! avdec_h264 ! videoconvert ! ximagesink name=sink", NULL);
//    pipeline = gst_parse_launch ("v4l2src device='/dev/video0' ! video/x-raw,width=320,height=240 ! videoconvert ! x264enc tune=zerolatency ! rtph264pay ! udpsink host='bta3 el computer' port=5022"
//                                 ,NULL);
//    pipeline2 = gst_parse_launch ("udpsrc port=10000 ! application/x-rtp,encoding-name=H264 ! rtpjitterbuffer latency=0 ! rtph264depay ! avdec_h264 ! videoconvert ! ximagesink", NULL);
    // prepare the ui

    /* Start playing */

//    sourcePipeline= gst_pipeline_new ("xvoverlay");
//    sourcePipeline = gst_parse_launch("v4l2src ! video/x-raw,width=640,height=480 ! videoconvert ! x264enc tune=zerolatency ! rtph264pay ! udpsink port=5022",NULL);


    pipeline = gst_pipeline_new ("xvoverlay");
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


    pipeline2 = gst_pipeline_new ("xvoverlay");
    source2=gst_element_factory_make("udpsrc","source2");
    buffer2=gst_element_factory_make("rtpjitterbuffer","buffer2");
    depay2=gst_element_factory_make("rtph264depay","depay2");
    decompressor2=gst_element_factory_make("avdec_h264","deco2");
    convert2=gst_element_factory_make("videoconvert","converter2");;
    sinkForWindow2=gst_element_factory_make("ximagesink","sinkForWindow2");


    if (!pipeline || !source || !tee || !queue1 || !queue2 || !sink || !depay || !buffer || !convert || !decompressor) {
       g_printerr ("Not all elements could be created.\n");
       return -1;
     }


    if (!pipeline2 || !source2 || !sinkForWindow2 || !depay2 || !buffer2 || !convert2 || !decompressor2) {
       g_printerr ("Not all elements could be created.\n");
       return -1;
     }


    caps= gst_caps_new_simple("application/x-rtp","media", G_TYPE_STRING, "video","encoding-name", G_TYPE_STRING,"H264",NULL);
    g_object_set(source,"port",5022,nullptr);
    g_object_set(source,"caps",caps, nullptr);
    g_object_set(buffer,"latency",0, nullptr);
    g_object_set(sink2,"port",10000,NULL);

    g_object_set(source2,"port",10000,nullptr);
    g_object_set(source2,"caps",caps, nullptr);
    g_object_set(buffer,"latency",0, nullptr);
    gst_caps_unref(caps);

    gst_bin_add_many (GST_BIN (pipeline), source, tee, queue1 , queue2, sink2, buffer,depay,decompressor,convert , sink, NULL);

    gst_bin_add_many (GST_BIN (pipeline2), source2, buffer2,depay2,decompressor2,convert2 , sinkForWindow2, NULL);



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


      if (!gst_element_link(source2,buffer2)){
          g_printerr("Error at linking source and buffer2");
          return 25;
      }
      if (!gst_element_link(buffer2,depay2)){
          g_printerr("Error at linking buffer and depay2");
          return 25;
      }
      if (!gst_element_link(depay2,decompressor2)){
          g_printerr("Error at linking depay and decompressore2");
          return 25;
      }

      if (!gst_element_link(decompressor2,convert2)){
          g_printerr("Error at linking decompressor and convert2");
          return 25;
      }

      if (!gst_element_link(convert2,sinkForWindow2)){
          g_printerr("Error at linking convert2 and sinkForWindow2");
          return 25;
      }


      WId xwinid = window->winId();
//    sink=gst_bin_get_by_name(GST_BIN(pipeline),"sink");
    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sink), xwinid);
//    timerLAbel->setParent(window);
//        layout->addWidget(window);
    /**********************************************************************************************/
    /*________________________________________*_*_*_*_*_*_*__*_*_*_*_*_*____________________________*/


    WId xwinid2 = window2->winId();
//    sinkForWindow2=gst_bin_get_by_name(GST_BIN(pipeline2),"ximagesink0");
    if (!sinkForWindow2){
        g_printerr("affafsdsgfs");
        return 15;
    }
    else
        g_printerr("AAAAAAAAAAAAAA");
    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sinkForWindow2), xwinid2);
    window2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    /*________________________________________*_*_*_*_*_*_*__*_*_*_*_*_*____________________________*/

    /**********************************************************************************************/
    // run the pipeline

    gst_element_set_state (pipeline2, GST_STATE_PLAYING);
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
      gst_object_unref (convert2);
      gst_object_unref (source2);
      gst_object_unref (decompressor2);
      gst_object_unref (depay2);
      gst_object_unref (pipeline2);
      gst_object_unref (buffer2);
      gst_object_unref (sinkForWindow2);
      gst_object_unref (source);
      // Exit application
      QTimer::singleShot(0, QApplication::activeWindow(), SLOT(quit()));
    }

    int ret = app.exec();

    window->hide();
    window2->hide();
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
    gst_object_unref (convert2);
    gst_object_unref (source2);
    gst_object_unref (decompressor2);
    gst_object_unref (depay2);
    gst_object_unref (pipeline2);
    gst_object_unref (buffer2);
    gst_object_unref (sinkForWindow2);
    gst_object_unref (source);




    return ret;

}


QWidget * gstream::getRenderingWindow(int windowNumber)
{
    if (windowNumber==2)
        return  window2;
    else
        return window;
}

