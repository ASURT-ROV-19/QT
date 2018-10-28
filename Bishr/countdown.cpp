#include "countdown.h"

CountDown::CountDown()
{
    timer=new QTimer(this);
    timer->setInterval(1000);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(changeTime()));
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

}
