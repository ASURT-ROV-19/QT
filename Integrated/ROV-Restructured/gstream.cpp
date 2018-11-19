#include "gstream.h"


gstream::gstream(QWidget *parent, QGridLayout *layout)
{
    window=new QWidget (parent);
    window2=new QWidget (parent);
    layout->addWidget(window,0,0);
    layout->addWidget(window2,0,1);
}

int gstream::setPipelines()
{

//creating elements

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


//checking whether all elements are created correctly or not


    if (!pipeline || !source || !tee || !queue1 || !queue2 || !sink || !depay || !buffer || !convert || !decompressor) {
       g_printerr ("Not all elements could be created.\n");
       return -1;
     }

    if (!pipeline2 || !source2 || !sinkForWindow2 || !depay2 || !buffer2 || !convert2 || !decompressor2 || !scaler) {
       g_printerr ("Not all elements could be created.\n");
       return -1;
     }
//creating capabilities and setting them to suit pipeline's data

    caps= gst_caps_new_simple("application/x-rtp","media", G_TYPE_STRING, "video","encoding-name", G_TYPE_STRING,"H264",NULL);

//setting caps and properties of elements

    g_object_set(source,"port",5022,nullptr);
    g_object_set(source,"caps",caps, nullptr);
    g_object_set(buffer,"latency",0, nullptr);
    g_object_set(sink2,"port",10000,NULL);
    g_object_set(source2,"port",10000,nullptr);
    g_object_set(source2,"caps",caps, nullptr);
    g_object_set(buffer,"latency",0, nullptr);

//adding packages of elements to piplines "setting piplines

    gst_bin_add_many (GST_BIN (pipeline), source, tee, queue1 , queue2, sink2, buffer,depay,decompressor,convert , sink, NULL);
    gst_bin_add_many (GST_BIN (pipeline2), source2, buffer2,depay2,decompressor2,scaler,capsfilter,convert2 , sinkForWindow2, NULL);

//connecting elements of both pipelines (this linking process must be ordered)

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
//these pads were created for linking tee and queues (the forking elements in the first pipeline) , now we have used them to link
//and already linked so we don't need them anymore

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


void gstream::setRenderingWindows()
{
    WId xwinid = window->winId();
//    sink=gst_bin_get_by_name(GST_BIN(pipeline),"sink");
  gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sink), xwinid);


  WId xwinid2 = window2->winId();
  gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (sinkForWindow2), xwinid2);

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
    g_main_loop_quit(mainLoop);
}

