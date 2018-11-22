#ifndef GUI_H
#define GUI_H
#include <QObject>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <countdown.h>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <QFont>
#include <QGridLayout>
#include "gstreamer.h"
//#include "gstream.h"
#include <QApplication>
#include <QString>
#include <string.h>
#include "buttonsconfiguration.h"

class gui : public QObject
{
    Q_OBJECT
public:
    gui(QWidget * parent=0);
    QPushButton * getChangingButton();    //temporary to use the button instead of the joystick as i ddon't have the joystick now;
    QGridLayout * getLayout();
    void addWidgetToLayout (QWidget * window,uint8_t row, uint8_t col , uint8_t width , uint8_t height,uint8_t windowNumber);

public slots:
    void changeInGUI(QString button);
    void changeButtonsConfiguration(QString newConfig);

signals:
    void pause_play();

private:
    QPushButton * button , * play_pause_button, * endButton;
    CountDown * timer;
    buttonsConfiguration * butConfig;
    QGridLayout * gridLay;
    QString cameraButton="2",timerButton="1";
    QWidget * window1,*window2,*window3;
};

#endif // GUI_H
