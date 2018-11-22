#ifndef COUNTDOWN_H
#define COUNTDOWN_H
#include <QTimer>
#include <math.h>
#include <QObject>
#include <QDebug>
#include <QLabel>
#include <QTime>

class CountDown : public QObject
{
    Q_OBJECT
public:
    CountDown();
    void setTimer(int minutes,int seconds);
    QString getTimeRemaining();
    void setTimerLabel();
    void setTimerFont();
    void setParent(QWidget * parent);
    QLabel * getTimerLabel();
    void pause();
    void resume();
public slots:
    void pause_Play();
    void changeTime();
    void resetDelay();
private:
    std::chrono::milliseconds  currentTime;
    QTime * TIME;
    QLabel * timerLabel;
    QTimer * timer;
    int mins=0,sec=0;
    QString time;
};

#endif // COUNTDOWN_H
