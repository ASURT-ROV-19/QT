#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<joystick_handler.h>
#include <tcpserver.h>
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
    ~MainWindow();
    MainWindow(QApplication * myApp);

private:
    Ui::MainWindow *ui;
    TCPServer *server;
    Joystick_Handler *joyS;
    QWidget * centralWidget;
    gui * GUI;

};

#endif // MAINWINDOW_H
