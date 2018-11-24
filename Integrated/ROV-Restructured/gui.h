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
#include <QTimer>
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
    void print();
    void prepButtonsConfig();
signals:
    void pause_play();
    void buttonsConfig(QString Configuration);
private:
    QTimer * tmr;
    QPushButton * button , * play_pause_button, * endButton;
    CountDown * timer;
    buttonsConfiguration * butConfig;
    QGridLayout * gridLay;
    QString cameraButton="2",timerButton="1",configurationButton="0";
    QString _cameraButton="2",_timerButton="1",_configurationButton="0";
    uint8_t windowSelector=0;
    void createWindows();
    void createButtons();
    void handleSignals();
    void checkForButtonsSwitch();
    gstream ** camera;
    QWidget ** window;
};

#endif // GUI_H
