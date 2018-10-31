#include "streamer.h"


streamer::streamer(QWidget * parent)
{/*

  * Local Videos Module
  * It doesn't support all videos extensions yet
  * only avi and wmv for now
  *
  *
*/
    medPl=new QMediaPlayer(parent);
    vw=new QVideoWidget(parent);
    medPl->setVideoOutput(vw);
//    medPl->setMedia(QUrl::fromLocalFile("Home/ASURT/QTProjects/Welcome/sample.avi"));
    vw->setGeometry(200,150,400,300);
    medPl->play();

/*
 * WebCam Module

    myCamera=new QCamera(parent);
    myCameraViewFinder=new QCameraViewfinder(parent);
    myCamera->setViewfinder(myCameraViewFinder);
    myCamera->start();
*/
}

/*
     //part of the WebCam module


QCameraViewfinder *streamer::getViewFinder()
{
    return myCameraViewFinder;
}

*/

/*
 *      //part of the local videos module
  */

