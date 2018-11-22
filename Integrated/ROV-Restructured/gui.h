#ifndef GUI_H
#define GUI_H
#include <QObject>
#include <QPushButton>
#include "countdown.h"
#include <QTimer>
#include <QDebug>
#include <QWidget>
#include <QFont>
#include <QGridLayout>
#include <QApplication>
#include <QString>
#include <string.h>
#include "buttonsconfiguration.h"
#include "gstream.h"

class gui : public QObject
{
    Q_OBJECT
public:
    gui(QWidget * parent=0);
    QPushButton * getChangingButton();    //temporary to use the button instead of the joystick as i ddon't have the joystick now;
    QGridLayout * getLayout();
    void getCam(gstream *Camera, uint8_t cameraNum);

public slots:
    void changeInGUI(QString button);
    void changeButtonsConfiguration(QString newConfig);
    void toggleCamera();

signals:
    void pause_play();

private:
    QPushButton * button , * play_pause_button, * endButton;
    CountDown * timer;
    buttonsConfiguration * butConfig;
    QGridLayout * gridLay;
    QString cameraButton="2",timerButton="1";
    QWidget ** window;
    uint8_t windowSelector=0;
    void createWindows();
    void createButtons();
    void handleSignals();
    gstream ** camera;
};

#endif // GUI_H
