#ifndef GUI_H
#define GUI_H
#include <QObject>
#include <QPushButton>
#include "guiItems/countdown.h"
#include <QTimer>
#include <QDebug>
#include <QWidget>
#include <QFont>
#include <QGridLayout>
#include <QApplication>
#include <QString>
#include <string.h>
#include "camera/gstreamer.h"
#include <QTimer>
#include "guiItems/sensorlabel.h"
#include <QProcess>

class gui : public QObject
{
    Q_OBJECT
public:
    gui(QWidget * parent=0);
    ~gui();
//    QPushButton * getChangingButton();    //temporary to use the button instead of the joystick as i ddon't have the joystick now;
//    void getCam(gstream *Camera, uint8_t cameraNum);
    void setDisplayWindow(QGst::Ui::VideoWidget *displayWindow, uint8_t cameraNum);
    void positionItems(QGst::Ui::VideoWidget * parent);
public slots:
    void changeInGUI(QString button);
    void changeInButtonsConfiguration(QString newConfig);
    void toggleCamera();
    void updateSensorLabel(QString depth);
signals:
    void pause_play();
    void restartTimer();
    void show_hideButConfig();
    void guiSizeChange();
private:

    void startLengthMeasuring();
    void createItems();
    void assignButtons();
    void handleSignals();
    void checkForButtonsSwitch(int buttonIndex,QString newNumber);
    bool switchButtons(QString * button1,QString * old_button1,QString * button2,QString * old_button2);

    sensorLabel * sensor_label;
    CountDown * timer;
    QGridLayout * guiLayout;
    uint8_t windowSelector=0;
//    gstream ** camera;
//    QWidget ** window;
    QVideoWidget ** videoWindow;
    QWidget * GUIwindow;
    QWidget * guiItemsCarryingWidget;
    QGridLayout * guiItemsLayout;
    QGst::Ui::VideoWidget ** videoDisplayer;
    QProcess * process;

    const int ZUpID=0,ZDownID=1,lightOnOffID=2,activateRID=3,restartTimerID=4,startLenMeasureID=5,buttonsSettingsID=6,changeCameraID=7,playPauseTimerID=8,fullScreenID=9;
    //    QString upZButton="0",activateR="1",lightOnOff="2",restartTimer="3",buttonsSettings="4",changeCamera="5",playPauseTimer="6";
    QString * buttons;
};

#endif // GUI_H
