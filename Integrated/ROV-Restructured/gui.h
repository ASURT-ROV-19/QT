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
//#include "buttonsconfiguration.h"
//#include "gstream.h"
#include "gstreamer.h"
#include <QTimer>
#include "sensorlabel.h"
#include <QProcess>

class gui : public QObject
{
    Q_OBJECT
public:
    gui(QWidget * parent=0);
//    QPushButton * getChangingButton();    //temporary to use the button instead of the joystick as i ddon't have the joystick now;
    QGridLayout * getLayout();
//    void getCam(gstream *Camera, uint8_t cameraNum);
    void getCam(gstreamer *Camera, uint8_t cameraNum);
    void positionItems(QGst::Ui::VideoWidget * parent);
public slots:
    void changeInGUI(QString button);
    void changeInButtonsConfiguration(QString newConfig);
    void prepButtonsConfig();
//    void changeCamerasSizes();
    void toggleCamera();
    void updateSensorLabel(QString depth);
signals:
    void pause_play();
    void restartTimer();
    void buttonsConfig(QString Configuration);
    void show_hideButConfig();
private:

    void startLengthMeasuring();
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
//    buttonsConfiguration * butConfig;
    QGridLayout * gridLay;
    uint8_t windowSelector=0;
//    gstream ** camera;
    gstreamer ** cameraZ;
//    QWidget ** window;
    QVideoWidget ** videoWindow;
    QWidget * GUIwindow;
    QWidget * dummyWidget,*realDummyDumb;
    QGridLayout * layTimer;
    QGst::Ui::VideoWidget ** videoDisplayer;
    QProcess * process;
/*
    jsButtons[0]->setInfo("Z axis Up                ","4","0");
    jsButtons[1]->setInfo("Z axis Down              ","2","1");
    jsButtons[2]->setInfo("light on/off             ","8","2");
    jsButtons[3]->setInfo("activate R               ","0","3");
    jsButtons[4]->setInfo("Restart Timer            ","3","4");
    jsButtons[5]->setInfo("Start Measuring Length   ","11","5");
    jsButtons[6]->setInfo("Buttons Settings         ","10","6");
    jsButtons[7]->setInfo("Change Camera            ","1","7");
    jsButtons[8]->setInfo("Play/Pause Timer         ","5","8");
*/
    const int ZUpID=0,ZDownID=1,lightOnOffID=2,activateRID=3,restartTimerID=4,startLenMeasureID=5,buttonsSettingsID=6,changeCameraID=7,playPauseTimerID=8;
    QString * buttons;
};

#endif // GUI_H
