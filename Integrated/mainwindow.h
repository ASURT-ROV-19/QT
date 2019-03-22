#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<joystick/joystick_handler.h>
#include <network/TCPConnection.h>
#include "gui.h"
#include "string.h"
#include <QApplication>
#include <QKeyEvent>
#include <QTimer>

#undef main

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setDisplayWindow(QGst::Ui::VideoWidget * displayWindow, uint8_t cameraNum);
    void setEndoscopeCamera(gstreamer * camera);
    ~MainWindow();
    void keyPressEvent(QKeyEvent * event);
private slots:
    void toggleFullScreen();
    void delayMicroCamDisplay();
signals:
    void showOrHideEndoscopeCamera();
    void endoToggleFullScreen();
    void messagePi(QString query);
    void playPauseTimer();
    void restartTimer();
private:
    void signalsHandler();
    Ui::MainWindow *ui;
    TCPConnection *TCPconnection;
    QWidget * centralWidget;
    Joystick_Handler *JSHandler;
    gui * GUI;
    int pulley,micro;
    QTimer * microDisplayDelayTimer;
};

#endif // MAINWINDOW_H
