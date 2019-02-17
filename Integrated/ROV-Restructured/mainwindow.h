#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<joystick_handler.h>
#include <tcpserver.h>
#include "gui.h"
#include "string.h"
#include <QApplication>
#include "buttonsconfiguration.h"

#undef main

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QGridLayout * getLayout();
    void getCam(gstream * camera, uint8_t cameraNum);
    void getCam(gstreamer * camera, uint8_t cameraNum);
    ~MainWindow();
    void createButtonsConfigurationWindow();

private:
    Ui::MainWindow *ui;
    TCPServer *server;
    Joystick_Handler *joyS;
    QWidget * centralWidget;
	Joystick_Handler *handler;
    gui * GUI;
    buttonsConfiguration * butConfig;
};

#endif // MAINWINDOW_H
