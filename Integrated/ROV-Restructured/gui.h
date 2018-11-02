#ifndef GUI_H
#define GUI_H
#include <QObject>
#include "gstream.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <countdown.h>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <QFont>
class gui : public QObject
{
    Q_OBJECT
public:
    gui(QWidget * parent=0);
private slots:
    void updateTimer();
public slots:
    void pause_play_Timer();
signals:
    void pause_play();
private:
    gstream * str;
    QVBoxLayout * verLay;
    QPushButton * button;
    CountDown * timer;
    QTimer * updater;
    QLabel * timerLabel;
    QLabel * pressureSensorLabel;
    QWidget * dummy;

};

#endif // GUI_H
