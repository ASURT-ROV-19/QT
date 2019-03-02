#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<joystick_handler.h>
#include <tcpserver.h>
#include "gui.h"
#include "string.h"
#include <QApplication>
#include "buttonsconfiguration.h"
#include "newsettingshandler.h"

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
//    void getCam(gstream * camera, uint8_t cameraNum);
    void setCam(gstreamer * camera, uint8_t cameraNum);
    ~MainWindow();
    void createSettingsHandler();
private slots:
    void toggleFullScreen();

private:
    Ui::MainWindow *ui;
    TCPServer *server;
    QWidget * centralWidget;
	Joystick_Handler *handler;
    gui * GUI;
    buttonsConfiguration * butConfig;
    newSettingsHandler * settingsHandler;
};

#endif // MAINWINDOW_H
