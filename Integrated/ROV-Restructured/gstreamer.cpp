
#include "gstreamer.h"

/*
    Actual constructor , the other is a copy for trials
    */
gstreamer::gstreamer(QWidget *parent, QVBoxLayout *layout)
{
    motherWidget=new QWidget();

    window=new QWidget();
    window->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    window2=new QWidget();
    window2->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    window->setStyleSheet("background-color: white");
//    window->setAttribute(Qt::WA_TranslucentBackground);
//    window->setStyleSheet("background:transparent;");
    window2->setStyleSheet("background-color: red");
    //    window=parent;
    horLay=new QHBoxLayout();
    horLay->addWidget(window);
    motherWidget->setLayout(horLay);
//    window->setGeometry(0,0,500,500);
//    layout->addWidget(window);
    layout->addWidget(motherWidget);
    vSpacer=new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Expanding);
    horLay->addWidget(window2);
//    horLay->addSpacerItem(vSpacer);
        layout->addSpacerItem(vSpacer);
}

gstreamer::gstreamer(QWidget *parent, QGridLayout *layout)
{
    motherWidget=new QWidget();

    window=new QWidget();
    window->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    window2=new QWidget();
    window2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    window->setStyleSheet("background-color: white");
//    window->setAttribute(Qt::WA_TranslucentBackground);
//    window->setStyleSheet("background:transparent;");
//    window2->setAttribute(Qt::WA_TranslucentBackground);
//    window2->setStyleSheet("background:transparent;");
    window2->setStyleSheet("background-color: red");
    layout->addWidget(window,1,0);
    layout->addWidget(window2,1,1);
    GUILayOut=layout;

}

void gstreamer::setWindowsSize()
{
    if (windowSelector==0){
        GUILayOut->removeWidget(window);
        GUILayOut->removeWidget(window2);
        GUILayOut->addWidget(window,1,0);
        GUILayOut->addWidget(window2,1,1);
        windowSelector++;
        g_print("Size 0\n");
    }
    else if (windowSelector==1){
        // Window 1 becomes the main camera window
        GUILayOut->removeWidget(window);
        GUILayOut->removeWidget(window2);
        GUILayOut->addWidget(window,1,0,1,5);
        GUILayOut->addWidget(window2,1,5,1,3);
        windowSelector++;
        g_print("Size 1\n");
    }
    else if (windowSelector==2){
//        Window 2 becomes the main camera window
        GUILayOut->removeWidget(window);
        GUILayOut->removeWidget(window2);
        GUILayOut->addWidget(window,1,0,1,3);
        GUILayOut->addWidget(window2,1,3,1,5);
        windowSelector-=2;
        g_print("Size 2\n");
    }

}

int gstreamer::action(QApplication * myApp)
{


    gst_init (0, 0);

    myApp->connect(myApp, SIGNAL(lastWindowClosed()), myApp, SLOT(quit ()));
    // prepare the pipeline

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
    convert2=gst_element_factory_make("videoconvert","converter2");
    sinkForWindow2=gst_element_factory_make("ximagesink","sinkForWindow2");
    scalingConvert=gst_element_factory_make("videoconvert","scalingConvert");
    scaler=gst_element_factory_make("videoscale","scaler0");
    capsfilter=gst_element_factory_make("capsfilter","filterForScaling");
    if (!pipeline || !source || !tee || !queue1 || !queue2 || !sink || !depay || !buffer || !convert || !decompressor) {
       g_printerr ("Not all elements could be created.\n");
       return -1;
     }
    if(!scaler){
        g_printerr("Scaler couldn't be created");
    }

    if (!pipeline2 || !source2 || !sinkForWindow2 || !depay2 || !buffer2 || !convert2 || !decompressor2) {
       g_printerr ("Not all elements could be created.\n");
       return -1;
     }
    scalingCaps=gst_caps_new_simple("video/x-raw","width",G_TYPE_INT,1280,"height",G_TYPE_INT,960,NULL);
//    gst_pad_set_caps(gst_element_get_request_pad(scaler, "src"),scalingCaps);

    caps= gst_caps_new_simple("application/x-rtp","media", G_TYPE_STRING, "video","encoding-name", G_TYPE_STRING,"H264",NULL);
    g_object_set(source,"port",5022,nullptr);
    g_object_set(source,"caps",caps, nullptr);
//    g_object_set(decompressor2,"caps",scalingCaps, nullptr);
    g_object_set(buffer,"latency",0, nullptr);
    g_object_set(sink2,"port",10000,NULL);
//    g_object_set(capsfilter,"width",320,NULL);
//    g_object_set(capsfilter,"height",320,NULL);
    g_object_set(source2,"port",10000,nullptr);
    g_object_set(source2,"caps",caps, nullptr);
    g_object_set(buffer,"latency",0, nullptr);
    gst_caps_unref(caps);
//    gst_element_link_filtered (scaler,convert2, scalingCaps);



    gst_bin_add_many (GST_BIN (pipeline), source, tee, queue1 , queue2, sink2, buffer,depay,decompressor,convert , sink, NULL);

    gst_bin_add_many (GST_BIN (pipeline2), source2, buffer2,depay2,decompressor2,scaler,capsfilter,convert2 , sinkForWindow2, NULL);



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

      if (!gst_element_link(decompressor2,scaler)){
          g_printerr("Error at linking decompressor and scaler");
          return 25;
      }

      if (!gst_element_link_filtered(scaler,convert2,scalingCaps)){
          g_printerr("Error at linking scaler and capsfilter");
          return 25;
      }

//      if (!gst_element_link(capsfilter,convert2)){
//          g_printerr("Error at linking capsfilter and convert2");
//          return 25;
//      }

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

    int ret = myApp->exec();

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
    gst_caps_unref(scalingCaps);

//    GMainLoop *loop=g_main_loop_new(NULL,FALSE);
//    g_main_loop_run(loop);

//    return ret;
    return 0;
}


QWidget * gstreamer::getRenderingWindow(int windowNumber)
{
    if (windowNumber==2)
        return  window2;
    else
        return window;
}

    /*
    The following large comment is to be uncommented and used instead of the one function "action()" above , to make
    the stream more controllable . I have just copied and pasted and thus commented it , but it will need refactoring and
    modifications before it can be used .
    */
//int gstreamer::setPipelines(){
//    pipeline = gst_pipeline_new ("xvoverlay");
//    source= gst_element_factory_make("udpsrc","source");
//    buffer=gst_element_factory_make("rtpjitterbuffer","buffer");
//    depay=gst_element_factory_make("rtph264depay","depay");
//    decompressor=gst_element_factory_make("avdec_h264","deco");
//    convert=gst_element_factory_make("videoconvert","converter");
//    sink=gst_element_factory_make("ximagesink","sink");
//    tee=gst_element_factory_make("tee","t1");
//    queue1=gst_element_factory_make("queue","queue1");
//    queue2=gst_element_factory_make("queue","queue2");
//    sink2=gst_element_factory_make("udpsink","sink2");


//    pipeline2 = gst_pipeline_new ("xvoverlay");
//    source2=gst_element_factory_make("udpsrc","source2");
//    buffer2=gst_element_factory_make("rtpjitterbuffer","buffer2");
//    depay2=gst_element_factory_make("rtph264depay","depay2");
//    decompressor2=gst_element_factory_make("avdec_h264","deco2");
//    convert2=gst_element_factory_make("videoconvert","converter2");
//    sinkForWindow2=gst_element_factory_make("ximagesink","sinkForWindow2");
//    scalingConvert=gst_element_factory_make("videoconvert","scalingConvert");
//    scaler=gst_element_factory_make("videoscale","scaler0");
//    capsfilter=gst_element_factory_make("capsfilter","filterForScaling");
//    if (!pipeline || !source || !tee || !queue1 || !queue2 || !sink || !depay || !buffer || !convert || !decompressor) {
//       g_printerr ("Not all elements could be created.\n");
//       return -1;
//     }
//    if(!scaler){
//        g_printerr("Scaler couldn't be created");
//        return -1;
//    }

//    if (!pipeline2 || !source2 || !sinkForWindow2 || !depay2 || !buffer2 || !convert2 || !decompressor2) {
//       g_printerr ("Not all elements could be created.\n");
//       return -1;
//     }
//    scalingCaps=gst_caps_new_simple("video/x-raw","width",G_TYPE_INT,1280,"height",G_TYPE_INT,960,NULL);
////    gst_pad_set_caps(gst_element_get_request_pad(scaler, "src"),scalingCaps);

//    caps= gst_caps_new_simple("application/x-rtp","media", G_TYPE_STRING, "video","encoding-name", G_TYPE_STRING,"H264",NULL);
//    g_object_set(source,"port",5022,nullptr);
//    g_object_set(source,"caps",caps, nullptr);
////    g_object_set(decompressor2,"caps",scalingCaps, nullptr);
//    g_object_set(buffer,"latency",0, nullptr);
//    g_object_set(sink2,"port",10000,NULL);
////    g_object_set(capsfilter,"width",320,NULL);
////    g_object_set(capsfilter,"height",320,NULL);
//    g_object_set(source2,"port",10000,nullptr);
//    g_object_set(source2,"caps",caps, nullptr);
//    g_object_set(buffer,"latency",0, nullptr);
//    gst_caps_unref(caps);
////    gst_element_link_filtered (scaler,convert2, scalingCaps);



//    gst_bin_add_many (GST_BIN (pipeline), source, tee, queue1 , queue2, sink2, buffer,depay,decompressor,convert , sink, NULL);

//    gst_bin_add_many (GST_BIN (pipeline2), source2, buffer2,depay2,decompressor2,scaler,capsfilter,convert2 , sinkForWindow2, NULL);



//        if (gst_element_link_many (buffer,depay,decompressor,convert , sink) != TRUE) {
//          g_printerr ("Elements could not be linked.\n");
//          gst_object_unref (pipeline);
//          gst_object_unref (decompressor);
//          gst_object_unref (depay);
//          gst_object_unref (buffer);
////          gst_object_unref (caps);
//          gst_object_unref (sink);
////          gst_object_unref (filter);
//          gst_object_unref (convert);
//          gst_object_unref (source);

//          return -1;
//      }else if (!gst_element_link(queue1,buffer)){
//          g_printerr("Error at linking queue1 and buffer");
//            return -1;
//      }
//        GstPad *teeDisplayPad = gst_element_get_request_pad(tee, "src_%u");
//        GstPad *queueDisplayPad = gst_element_get_static_pad(queue1, "sink");

//        GstPad *teeRecordPad = gst_element_get_request_pad(tee, "src_%u");
//        GstPad *queueRecordPad = gst_element_get_static_pad(queue2, "sink");

//        if(gst_pad_link(teeDisplayPad, queueDisplayPad) != GST_PAD_LINK_OK){
//            g_print("Unable to link tee and queue1");
//        }

//        if(gst_pad_link(teeRecordPad, queueRecordPad) != GST_PAD_LINK_OK){
//            g_print("Unable to link tee and queue2");
//            return -1;
//        }
//        if (!gst_element_link(queue2,sink2)){
//            g_print("Unable to link queue2 and sink2");
//            return -1;
//        }

//        //gst_object_unref(teeDisplayPad);
//        gst_object_unref(queueDisplayPad);
//        //gst_object_unref(teeRecordPad);
//        gst_object_unref(queueRecordPad);

//      if (!gst_element_link(source,tee)){
//          g_printerr("Error at linking source and buffer");
//          gst_object_unref (pipeline);
//          gst_object_unref (decompressor);
//          gst_object_unref (depay);
//          gst_object_unref (buffer);
////          gst_object_unref (caps);
//          gst_object_unref (sink);
////          gst_object_unref (filter);
//          gst_object_unref (convert);
//          gst_object_unref (source);
//          return -1;
//      }


//      if (!gst_element_link(source2,buffer2)){
//          g_printerr("Error at linking source and buffer2");
//          return 25;
//      }
//      if (!gst_element_link(buffer2,depay2)){
//          g_printerr("Error at linking buffer and depay2");
//          return 25;
//      }
//      if (!gst_element_link(depay2,decompressor2)){
//          g_printerr("Error at linking depay and decompressore2");
//          return 25;
//      }

//      if (!gst_element_link(decompressor2,scaler)){
//          g_printerr("Error at linking decompressor and scaler");
//          return 25;
//      }

//      if (!gst_element_link_filtered(scaler,convert2,scalingCaps)){
//          g_printerr("Error at linking scaler and capsfilter");
//          return 25;
//      }

////      if (!gst_element_link(capsfilter,convert2)){
////          g_printerr("Error at linking capsfilter and convert2");
////          return 25;
////      }

//      if (!gst_element_link(convert2,sinkForWindow2)){
//          g_printerr("Error at linking convert2 and sinkForWindow2");
//          return 25;
//      }


//      WId xwinid = window->winId();
////    sink=gst_bin_get_by_name(GST_BIN(pipeline),"sink");
//    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sink), xwinid);
////    timerLAbel->setParent(window);
////        layout->addWidget(window);
//    /**********************************************************************************************/
//    /*________________________________________*_*_*_*_*_*_*__*_*_*_*_*_*____________________________*/


//    WId xwinid2 = window2->winId();
////    sinkForWindow2=gst_bin_get_by_name(GST_BIN(pipeline2),"ximagesink0");
//    if (!sinkForWindow2){
//        g_printerr("affafsdsgfs");
//        return 15;
//    }
//    else
//        g_printerr("AAAAAAAAAAAAAA");
//    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sinkForWindow2), xwinid2);
//    window2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


//}


//void gstreamer::setReady(){
//    gst_element_set_state (pipeline2, GST_STATE_READY);
//    GstStateChangeReturn sret = gst_element_set_state (pipeline,
//        GST_STATE_READY);


//}


//void gstreamer::play(){
//    gst_element_set_state (pipeline2, GST_STATE_PLAYING);
//    GstStateChangeReturn sret = gst_element_set_state (pipeline,
//        GST_STATE_PLAYING);


//}


//void gstreamer:: stop(){
//    gst_element_set_state (pipeline2, GST_STATE_PAUSED);
//    GstStateChangeReturn sret = gst_element_set_state (pipeline,
//        GST_STATE_PAUSED);



//}


//gstreamer::~gstreamer(){


//}
