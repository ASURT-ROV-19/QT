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
#include "sensorlabel.h"

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
    void updateSensorLabel(QString depth);
signals:
    void pause_play();
    void restartTimer();
    void buttonsConfig(QString Configuration);
private:

    void createWindows();
    void createButtons();
    void assignButtons();
    void handleSignals();
    void checkForButtonsSwitch(int buttonIndex,QString newNumber);
    bool switchButtons(QString * button1,QString * old_button1,QString * button2,QString * old_button2);

    sensorLabel * sensor_label;
    QString configuration;
    QTimer * tmr,*tmr2;
    QPushButton * button , * play_pause_button, * endButton;
    CountDown * timer;
    buttonsConfiguration * butConfig;
    QGridLayout * gridLay;
    uint8_t windowSelector=0;
    gstream ** camera;
    gstreamer ** cameraZ;
//    QWidget ** window;
    QVideoWidget ** videoWindow;
    QWidget * GUIwindow;
    QWidget * dummyWidget,*realDummyDumb;
    QGridLayout * layTimer;
    QGst::Ui::VideoWidget ** videoDisplayer;


    QString cameraButton="2",timerButton="11",configurationButton="0",restart_timer="3",upZButton="4",rActive="5",light="6";
    QString _cameraButton="2",_timerButton="11",_configurationButton="0",_restart_timer="3",_upZButton="4",_rActive="5",_light="6";

    QString ** buttons;
    QString ** _buttons;

};

#endif // GUI_H
