#ifndef COUNTDOWN_H
#define COUNTDOWN_H
#include <QTimer>
#include <math.h>
#include <QObject>
#include <QDebug>
class CountDown : public QObject
{
    Q_OBJECT
public:
    CountDown();
    void setTimer(int minutes,int seconds);

    QString getTimeRemaining();
public slots:
    void pause();
    void resume();
    void changeTime();
private:
    QTimer * timer;
    int mins=0,sec=0;
    QString time;
};

#endif // COUNTDOWN_H
