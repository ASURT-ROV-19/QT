#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<joystick/joystick_handler.h>
#include <network/TCPConnection.h>
#include "gui.h"
#include "string.h"
#include <QApplication>

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
    ~MainWindow();
private slots:
    void toggleFullScreen();

private:
    Ui::MainWindow *ui;
    TCPConnection *TCPconnection;
    QWidget * centralWidget;
    Joystick_Handler *JSHandler;
    gui * GUI;
};

#endif // MAINWINDOW_H
