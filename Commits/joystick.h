#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>
#include <QTimer>
#include <QDebug>
#include <QMainWindow>

class joystick : public QMainWindow
{
    Q_OBJECT


public:
    joystick();
    void ProcImgSend();

signals:
    void streamData(QString data);
    void streamOrder(QString order);

public slots:
    void JSLoop();
    void print();
    void JSDataReady(QString messageToConvey);
    void JSDataReady();
    void JSOrderRead();


private:
    SDL_Joystick * js;
    SDL_Event * event;
    int minX=100,maxX=-100,minY=100,maxY=-100,minZ=100,maxZ=-100,maxR=-100,minR=100;
    int map(int value);
    QTimer * timerJS;
    int x=0,y=0,z=0,r=0;
    QString info;
    QObject * mainWindow;
    int change=0;
//    char * data;
};

#endif // JOYSTICK_H
