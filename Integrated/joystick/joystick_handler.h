#ifndef JOYSTICK_HANDLER_H
#define JOYSTICK_HANDLER_H
#include <QTimer>
#include <string.h>
#include <QString>
#include <QDebug>
#include <joystick/joystick.h>

using namespace std;

class Joystick_Handler: public QObject
{
    Q_OBJECT

public:
    Joystick_Handler();
    ~Joystick_Handler();
//    void getMessage(QString message, int serverOrGui);

public slots:
//    void changeInButtonsConfiguration(QString newConfig);
    void joyAxisMotion();
    void updateCamOnFocus(int cam);
private slots:
    void messageReady(QString message);
    void buttonDown(int button);
    void buttonUp(int button);
signals:
    void sendToPi(QString);
    void guiChange(QString);
    void sendZDirection(QString);
private:
//    void buttonDownMessage();
//    void buttonUpMessage();
    int mapZ();
    int map(int axisValue);
    void move();
    void signalsHandler();
    void change_prev();

    QString msg;
    int prev_x,prev_y,prev_z,prev_r,upZ=0,getTemperature=0,axisChangeFlag=0,activateR=0,zMode,cam;
    Joystick * joyS;
    int numOfPiButtons;
    int * buttons;
    int camOnFocus=1;
};

#endif // JOYSTICK_HANDLER_H
