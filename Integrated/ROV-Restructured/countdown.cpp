#include "countdown.h"

CountDown::CountDown()
{
    TIME=new QTime();
//    currentTime=TIME->second();
    timer=new QTimer(this);
    timer->setInterval(1000);
    setTimerLabel();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(changeTime()));
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(resetDelay()));

}


void CountDown::setTimer(int minutes,int seconds){
    timer->start();
    mins =abs(minutes);
    sec=abs(seconds);
    if (sec>=60){
        mins+=floor(sec/60);
        sec=sec%60;
    }

}

void CountDown::pause()
{
//    currentTime=std::tan();
    TIME->setHMS(0,0,0,0);
    timer->stop();
    TIME->start();
}

void CountDown::resume()
{
//    currentTime
//    timer->setInterval(1000-currentTime);
    timer->start();

}

void CountDown::pause_Play()
{
    timer->isActive() ? pause():resume();
}


QString CountDown::getTimeRemaining(){
    return time;
}

void CountDown::changeTime()
{
    sec-=1;
    if (sec<0){
        if (mins>0){
            mins--;
            sec=59;
        }
        else {
            time="TIME OUT !!!!";
            return;
        }
    }
    if (mins<10){
        time="0"+QString::number(mins)+":";
    }
    else{
        time=QString::number(mins)+":";
    }
    if  (sec<10){
        time+="0"+QString::number(sec);
    }
    else{
        time+=QString::number(sec);
    }

    timerLabel->setText(time);
}

void CountDown::resetDelay()
{
    timer->setInterval(1000);
}


void CountDown::setTimerLabel(){
    timerLabel=new QLabel(time);
    timerLabel->setGeometry(0,0,100,00);
    timerLabel->show();
    setTimerFont();
    timerLabel->setAttribute(Qt::WA_TranslucentBackground);
    timerLabel->setStyleSheet("background:transparent;");
}

void CountDown::setTimerFont()
{
    QFont font1=timerLabel->font();
    font1.setPointSize(18);
    timerLabel->setFont(font1);

}

void CountDown::setParent(QWidget *parent)
{
    timerLabel->setParent(parent);
}

QLabel *CountDown::getTimerLabel()
{
    return timerLabel;
}
