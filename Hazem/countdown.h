#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QObject>
#include <QWidget>
#include<string.h>
#include<QPushButton>
#include <QTimer>
#include <QMainWindow>

using namespace std;

class Countdown: public QObject
{
    Q_OBJECT
public:

    Countdown(QMainWindow *window);

private:
    QPushButton *counter,*text;
    QTimer *timer;
    int minutes,seconds;
    string s;


public slots:
    void update();
};

#endif // COUNTDOWN_H
