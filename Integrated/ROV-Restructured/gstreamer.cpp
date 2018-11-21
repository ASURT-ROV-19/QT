
#include "gstreamer.h"




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
        //two windows of equal size
        GUILayOut->removeWidget(window);
        GUILayOut->removeWidget(window2);
        GUILayOut->addWidget(window,1,0);
        GUILayOut->addWidget(window2,1,1);
        windowSelector++;
        g_print("Size 0\n");
    }
    else if (windowSelector==1){
        // Window 1 becomes the main camera window
//        changeDisplaySize(200,200);
        /*
        in the previous commented , function i was trying to have control over display size at the receiver , it hadn't worked yet
        but shall it work , it would make us able to change size of display without any change on the the raspberry pi
        */
        GUILayOut->removeWidget(window);
        GUILayOut->removeWidget(window2);
        GUILayOut->addWidget(window,1,0,1,8);
        GUILayOut->addWidget(window2,1,8,1,3);
        windowSelector++;
        g_print("Size 1\n");
    }
    else if (windowSelector==2){
//        Window 2 becomes the main camera window
        GUILayOut->removeWidget(window);
        GUILayOut->removeWidget(window2);
        GUILayOut->addWidget(window,1,0,1,3);
        GUILayOut->addWidget(window2,1,3,3,8);
        windowSelector-=2;
        g_print("Size 2\n");
    }

}


void gstreamer::autoSetPipelines()
{
    pipeline=gst_pipeline_new("xvoverlay");
//    pipeline=gst_parse_launch("udpsrc port=5022 ! application/x-rtp,encoding-name=H264 ! tee name='t1' ! queue ! rtpjitterbuffer ! rtph264depay ! avdec_h264 ! videoconvert ! ximagesink name=sink .t1 ! queue ! udpsink port=10000",NULL);
    pipeline=gst_parse_launch("udpsrc port=5022 ! application/x-rtp,encoding-name=JPEG,payload=26 ! tee name='t1' ! queue ! udpsink port=10000 t1. ! queue ! rtpjpegdepay ! jpegdec idct-method=2 ! videoconvert ! ximagesink name=sink",NULL);
//the JPEG pipeline now works on an external terminal , don't currently know exactly what its problem here is , but probably it's a rendenring issue
    //as am also facing a rendering unsolved issue in the auto H264 Pipeline
    pipeline2=gst_pipeline_new("xvoverlay");
//    pipeline2=gst_parse_launch("udpsrc port=10000 ! application/x-rtp,encoding-name=H264 ! rtpjitterbuffer ! rtph264depay ! avdec_h264 ! videoconvert ! videoscale ! video/x-raw,width=100 ! ximagesink name=sink",NULL);
    pipeline2=gst_parse_launch("udpsrc port=10000 ! application/x-rtp,encoding-name=JPEG,payload=26 ! rtpjpegdepay ! jpegdec idct-method=2 ! videoconvert ! ximagesink name=sink",NULL);
}



int gstreamer::setPipelines()
{
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

    if (!pipeline2 || !source2 || !sinkForWindow2 || !depay2 || !buffer2 || !convert2 || !decompressor2 || !scaler) {
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
    g_object_set(buffer2,"latency",0, nullptr);

    gst_bin_add_many (GST_BIN (pipeline), source, tee, queue1 , queue2, sink2, buffer,depay,decompressor,convert , sink, NULL);

    gst_bin_add_many (GST_BIN (pipeline2), source2, buffer2,depay2,decompressor2,scaler,capsfilter,convert2 , sinkForWindow2, NULL);



        if (gst_element_link_many (buffer,depay,decompressor,convert , sink) != TRUE) {
          g_printerr ("Elements could not be linked.\n");
          return -1;
      }else if (!gst_element_link(queue1,buffer)){
          g_printerr("Error at linking queue1 and buffer");
            return -1;
      }
        GstPad *teeDisplayPad1 = gst_element_get_request_pad(tee, "src_%u");
        GstPad *queueDisplayPad1 = gst_element_get_static_pad(queue1, "sink");

        GstPad *teeDisplayPad2 = gst_element_get_request_pad(tee, "src_%u");
        GstPad *queueDisplayPad2 = gst_element_get_static_pad(queue2, "sink");

        if(gst_pad_link(teeDisplayPad1, queueDisplayPad1) != GST_PAD_LINK_OK){
            g_print("Unable to link tee and queue1");
        }

        if(gst_pad_link(teeDisplayPad2, queueDisplayPad2) != GST_PAD_LINK_OK){
            g_print("Unable to link tee and queue2");
            return -1;
        }
        if (!gst_element_link(queue2,sink2)){
            g_print("Unable to link queue2 and sink2");
            return -1;
        }

        gst_object_unref(teeDisplayPad1);
        gst_object_unref(queueDisplayPad1);
        gst_object_unref(teeDisplayPad2);
        gst_object_unref(queueDisplayPad2);

      if (!gst_element_link(source,tee)){
          g_printerr("Error at linking source and buffer");
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
      scalingCaps=gst_caps_new_simple("video/x-raw","width",G_TYPE_INT,1280,"height",G_TYPE_INT,960,NULL);
      if (!gst_element_link_filtered(scaler,convert2,scalingCaps)){
          g_printerr("Error at linking scaler and capsfilter");
          return 25;
      }

      if (!gst_element_link(convert2,sinkForWindow2)){
          g_printerr("Error at linking convert2 and sinkForWindow2");
          return 25;
      }

}

void gstreamer::setRenderingWindows()
{
    WId xwinid = window->winId();
//    sink=gst_bin_get_by_name(GST_BIN(pipeline),"sink");  //uncomment this if you use the autoSetPipelines Function;
  gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sink), xwinid);


  WId xwinid2 = window2->winId();
//    sinkForWindow2=gst_bin_get_by_name(GST_BIN(pipeline2),"sink");  //uncomment this if you use the autoSetPipelines Function;
  gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sinkForWindow2), xwinid2);

}

void gstreamer::changeDisplaySize(int height, int width)
{
    g_print("asdadsasd\n");
    gst_element_set_state (pipeline2, GST_STATE_NULL);
//    gst_element_set_state (pipeline,GST_STATE_READY);streamer
    gst_element_unlink_many( tee,source2, buffer2,depay2,decompressor2,scaler,convert2 ,sinkForWindow2,NULL);
    gst_bin_remove_many(GST_BIN (pipeline2),convert2,scaler, NULL);
    gst_object_unref (scaler);
    gst_object_unref (convert2);
    scaler=gst_element_factory_make("videoscale","scaler0");
    convert2=gst_element_factory_make("videoconvert","convert2");
    gst_bin_add_many(GST_BIN(pipeline2),scaler,convert2,NULL);
    g_object_set(source2,"caps",caps, nullptr);
    if (!gst_element_link(source2,buffer2)){
        g_printerr("Error at relinking source and buffer2");
    }
    else{
        g_print("1\n");
    }

    if (!gst_element_link(buffer2,depay2)){
        g_printerr("Error at relinking buffer and depay2");
    }
    else{
        g_print("2\n");
    }
    if (!gst_element_link(depay2,decompressor2)){
        g_printerr("Error at relinking depay and decompressore2");
    }
    else{
        g_print("3\n");
    }

    if (!gst_element_link(decompressor2,scaler)){
        g_printerr("Error at relinking decompressor and scaler");
    }

    else{
        g_print("4\n");
    }
    scalingCaps=gst_caps_new_simple("video/x-raw","width",G_TYPE_INT,1280,"height",G_TYPE_INT,960,NULL);

    if (!gst_element_link_filtered(scaler,convert2,scalingCaps)){
        g_printerr("Error at relinking scaler and capsfilter");
    }
    else{
        g_print("5\n");
    }
    if (!gst_element_link(convert2,sinkForWindow2)){
        g_printerr("Error at relinking convert2 and sinkForWindow2");
    }
    else{
        g_print("6\n");
    }
    gst_element_set_state (pipeline2, GST_STATE_PLAYING);

}


void gstreamer::play_pause()
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

void gstreamer::quitProgram()
{
    g_print("shall end loop\n");
    g_main_loop_quit(mainLoop);
    //shall also call for qApp exit here;

}



int gstreamer::action(QApplication * myApp)
{

    gst_init (0, 0);

    myApp->connect(myApp, SIGNAL(lastWindowClosed()), this, SLOT(quitProgram()));

// prepare the pipeline
//    sourcePipeline= gst_pipeline_new ("xvoverlay");
//    sourcePipeline = gst_parse_launch("v4l2src ! video/x-raw,width=640,height=480 ! videoconvert ! x264enc tune=zerolatency ! rtph264pay ! udpsink port=5022",NULL);


//    autoSetPipelines();
    setPipelines();
    setRenderingWindows();



// run the pipeline

    GstStateChangeReturn sret = gst_element_set_state (pipeline,GST_STATE_PLAYING);
    gst_element_set_state (pipeline2, GST_STATE_PLAYING);

    if (sret == GST_STATE_CHANGE_FAILURE) {
      gst_element_set_state (pipeline, GST_STATE_NULL);
      // Exit application
      QTimer::singleShot(0, QApplication::activeWindow(), SLOT(quit()));
//      QTimer::singleShot(0, this, SLOT(endMainLoop()));
            }
    else{
        state=1;
    }

    int ret = myApp->exec();
    mainLoop=g_main_loop_new(NULL,FALSE);
//    g_main_loop_run (mainLoop);
    window->hide();
    window2->hide();
    gst_element_set_state (pipeline, GST_STATE_NULL);


//    GMainLoop *loop=g_main_loop_new(NULL,TRUE);
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



gstreamer::~gstreamer(){
    gst_object_unref (pipeline);
    gst_object_unref (pipeline2);
    gst_object_unref (source);
    gst_object_unref (source2);
    gst_object_unref (decompressor);
    gst_object_unref (decompressor2);
    gst_object_unref (depay);
    gst_object_unref (depay2);
    gst_object_unref (buffer);
    gst_object_unref (buffer2);
    gst_object_unref (sink);
    gst_object_unref (sink2);
    gst_object_unref (sinkForWindow2);
    gst_object_unref (tee);
    gst_object_unref (queue1);
    gst_object_unref (queue2);
    gst_object_unref (convert);
    gst_object_unref (convert2);
    gst_object_unref (pipeline2);
    gst_caps_unref(caps);
    gst_caps_unref(scalingCaps);
    gst_caps_unref(caps);


}
