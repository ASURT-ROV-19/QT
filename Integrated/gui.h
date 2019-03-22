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
#include <QSpacerItem>
#include <QApplication>
#include <QString>
#include <string.h>
#include "camera/gstreamer.h"
#include <QTimer>
#include "guiItems/transparentlabel.h"
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
    void positionItems(QGridLayout * parent);
    void setEndoscopeCamera(gstreamer * endoscopeCamera);
public slots:
    void changeInGUI(QString button);
    void changeInButtonsConfiguration(QString newConfig);
    void toggleCamera();
    void receiveFromPi(QString temp);
    void updateZdirection(QString direction);
    void showOrHideEndoscopeCamera();
    void showOrHideTempLabel();
    void startLengthMeasuring();
    void toggleEndoFullScreen();
    void pause_play();
    void restartTimer();
signals:
    void show_hideButConfig();
    void guiSizeChange();
private:
    void createLayouts();
    void setCameraWindowLayout(int cameraIndex);
    void createItems();
    void assignButtons();
    void handleSignals();

    QLabel * temperatureLabel;
    transparentLabel * sensor_label;
    transparentLabel * cameraLabel;
    transparentLabel * zDirection;
    CountDown * timer;
    QGridLayout * guiLayout;
    QGridLayout ** camsLayout;
    QGridLayout * guiItemsLayout;
    QSpacerItem * verticalSpacer;
    uint8_t windowSelector;
    gstreamer * endoscopeCamera;
//    gstream ** camera;
//    QWidget ** window;
    QVideoWidget ** videoWindow;
    QWidget * GUIwindow;
    QWidget * guiItemsCarryingWidget;
    QGst::Ui::VideoWidget ** videoDisplayer;
    QProcess * process;

    //    QString upZButton="0",activateR="1",lightOnOff="2",restartTimer="3",buttonsSettings="4",changeCamera="5",playPauseTimer="6";
    QString * buttons;
};

#endif // GUI_H
