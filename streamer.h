#ifndef STREAMER_H
#define STREAMER_H
#include <QVBoxLayout>
//#include <QHBoxLayout>
//#include <QSpacerItem>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QWidget>




class streamer : public QMainWindow
{
public:
    streamer(QWidget * parent);
//    QCameraViewfinder * getViewFinder();
    QVideoWidget * getVideoWidget();               //part of the local videos module
private:
    QMediaPlayer * medPl;                          //part of the local videos module
    QVideoWidget * vw;                              //part of the local videos module
//    QCamera * myCamera;                              //part of the WebCam module
//    QCameraViewfinder * myCameraViewFinder;          //part of the WebCam module
//    QCameraImageCapture * myCameraImageCapture;      //part of the WebCam module



};

#endif // STREAMER_H
