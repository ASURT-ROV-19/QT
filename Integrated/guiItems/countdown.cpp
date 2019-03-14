#include "countdown.h"
#include <QDateTime>
CountDown::CountDown()
{
    elapsed=new QElapsedTimer();
    timer=new QTimer(this);
    timer->setInterval(1000);
    setTimerLabel();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(changeTime()));
}



void CountDown::setTimer(int minutes,int seconds){
    mins =abs(minutes);
    sec=abs(seconds);
    if (sec>=60){
        mins+=floor(sec/60);
        sec=sec%60;
    }
    changeTime();

}

void CountDown::pause()
{
    timer->stop();
}

void CountDown::resume()
{
    timer->start();
}

void CountDown::setBackgroundColor()
{
    if (mins < 2){
        timerLabel->setStyleSheet("QLabel{color: red ;  font-size: 33px; }");
    }
    else if (mins < 5){
        timerLabel->setStyleSheet("QLabel{color: orange ;  font-size: 33px; }");

    }
    else if (mins < 14){
        timerLabel->setStyleSheet("QLabel{color: yellow ;  font-size: 33px; }");
    }
    else {
        timerLabel->setStyleSheet("QLabel{color: green ;  font-size: 33px; }");
    }
}

void CountDown::restartTimer(int minutes,int seconds){
    mins=minutes;
    sec=seconds;
    timer->stop();
    timer->start();
}

CountDown::~CountDown()
{
    qDebug()<<"destroying countDown instance";
    delete TIME;
    delete timerLabel;
    delete timer;
    delete elapsed;
}



void CountDown::pause_Play()
{
    if(timer->isActive()){
        delay=0;
        delay=elapsed->elapsed();
        pause();
    }
    else{
        resetDelay();
        resume();
    }
}

QString CountDown::getTimeRemaining(){
    return time;
}

void CountDown::changeTime()
{

    sec-=1;
    elapsed->start();
    delay=0;
    resetDelay();
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
    time=QString("%1").arg( mins, 2 , 10, QChar('0'))+ ":" +QString("%1").arg( sec, 2 , 10, QChar('0'));
    setBackgroundColor();
    updateText();
}

void CountDown::resetDelay()
{
    timer->setInterval(1000-delay);
}

void CountDown::updateText()
{
    timerLabel->setUpdatesEnabled(true);
    timerLabel->setText(time);
}


void CountDown::setTimerLabel()
{
    timerLabel=new QLabel(time);
    timerLabel->setGeometry(0,0,115,50);
    timerLabel->show();
    setTimerFont();
    timerLabel->setAttribute(Qt::WA_TranslucentBackground);

}

void CountDown::setTimerFont()
{
    QFont font1=timerLabel->font();
    font1.setPointSize(26);
    timerLabel->setFont(font1);
     timerLabel->setStyleSheet("QLabel{color: orange ;  font-size: 33px; }");

}

void CountDown::setParent(QWidget *parent)
{
    qDebug()<<&parent<<" IN COUNTDOWN";
    timerLabel->setParent(parent);
}

QLabel *CountDown::getTimerLabel()
{
    return timerLabel;
}
