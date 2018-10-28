
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QMainWindow>
#include "streamer.h"
#include <QWidget>
#include <QPushButton>
#include "udpsocket.h"
#include "gstream.h"
#include <QSignalMapper>
#include <QtDebug>
#include <QTimer>
#include "jsinterface.h"
#include "gui.h"
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
//    streamer * stream;
    QVBoxLayout * verLay;
    QHBoxLayout * horLay;
    QSpacerItem * vSpacer;
    QPushButton * bttn1;
    QWidget * centralWidget;
    QPushButton * bttnPrint;
//    tcpsocket * ImageProcessingSock;
    gstream * str;
    QWidget * streamingWidget;
    JSInterface controller;
    gui * GUI;
};

#endif // MAINWINDOW_H
