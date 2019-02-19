#ifndef COUNTDOWN_H
#define COUNTDOWN_H
#include <QTimer>
#include <math.h>
#include <QObject>
#include <QDebug>
#include <QLabel>
#include <QTime>
#include <QElapsedTimer>

class CountDown : public QObject
{
    Q_OBJECT
public:
    CountDown();
    CountDown(QWidget * parent);
    void setTimer(int minutes,int seconds);
    QString getTimeRemaining();
    void setTimerLabel(QWidget * parent);
    void setTimerLabel();
    void setTimerFont();
    void setParent(QWidget * parent);
    QLabel * getTimerLabel();
    void pause();
    void resume();
    void restart();
    void setBackgroundColor();
    void restartTimer(int minutes,int seconds);

    ~CountDown();
public slots:
    void pause_Play();
    void changeTime();
    void resetDelay();
    void updateText();
private:
    int delay;
    QTime * TIME;
    QLabel * timerLabel;
    QTimer * timer;
    int mins=0,sec=0;
    QString time;
    QElapsedTimer * elapsed;
};

#endif // COUNTDOWN_H
