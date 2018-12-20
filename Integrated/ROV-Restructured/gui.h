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
#include "gstreamer.h"
#include <QTimer>

class gui : public QObject
{
    Q_OBJECT
public:
    gui(QWidget * parent=0);
//    QPushButton * getChangingButton();    //temporary to use the button instead of the joystick as i ddon't have the joystick now;
    QGridLayout * getLayout();
    void getCam(gstream *Camera, uint8_t cameraNum);
    void getCam(gstreamer *Camera, uint8_t cameraNum);
    void positionItems(QGst::Ui::VideoWidget * parent);

public slots:
    void changeInGUI(QString button);
    void changeButtonsConfiguration(QString newConfig);
    void prepButtonsConfig();
//    void changeCamerasSizes();
    void toggleCamera();
signals:
    void pause_play();
    void restartTimer();
    void buttonsConfig(QString Configuration);
private:

    void createWindows();
    void createButtons();
    void handleSignals();
    void checkForButtonsSwitch();
    void switchButtons(QString * button1,QString * old_button1,QString * button2,QString * old_button2);


    QTimer * tmr,*tmr2;
    QPushButton * button , * play_pause_button, * endButton;
    CountDown * timer;
    buttonsConfiguration * butConfig;
    QGridLayout * gridLay;
    QString cameraButton="2",timerButton="1",configurationButton="0",restart_timer="3";
    QString _cameraButton="2",_timerButton="1",_configurationButton="0",_restart_timer="3";
    uint8_t windowSelector=0;
    gstream ** camera;
    gstreamer ** cameraZ;
//    QWidget ** window;
    QVideoWidget ** videoWindow;
    QWidget * GUIwindow;
    QWidget * dummyWidget,*realDummyDumb;
    QGridLayout * layTimer;

    QGst::Ui::VideoWidget ** videoDisplayer;
};

#endif // GUI_H
