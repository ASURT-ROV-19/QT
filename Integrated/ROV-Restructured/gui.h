#ifndef GUI_H
#define GUI_H
#include <QObject>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <countdown.h>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <QFont>
#include <QGridLayout>
#include "gstreamer.h"
#include <QApplication>
#include <QString>
#include <string.h>
class gui : public QObject
{
    Q_OBJECT
public:
    gui(QWidget * parent=0);
    void startListening(QApplication * myApp);
private slots:
    void updateTimer();
public slots:
    void changeInGUI(QString button);
signals:
    void pause_play();
private:
//    gstream * str;
    gstreamer * streamer;
    QVBoxLayout * verLay;
    QPushButton * button;
    CountDown * timer;
    QTimer * updater;
    QLabel * timerLabel;
    QLabel * pressureSensorLabel;
    QWidget * dummy;

    // Temporary layout to try for displaying timer on rendering window
    QGridLayout * gridLay;

};

#endif // GUI_H
