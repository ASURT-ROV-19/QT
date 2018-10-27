#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<joystick_handler.h>
#include <countdown.h>

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

private:
    Ui::MainWindow *ui;
    Countdown *countd;


};

#endif // MAINWINDOW_H
