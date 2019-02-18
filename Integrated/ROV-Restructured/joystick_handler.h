#ifndef JOYSTICK_HANDLER_H
#define JOYSTICK_HANDLER_H
#include <QTimer>
#include <string.h>
#include <QString>
#include <QDebug>
#include <joystick.h>

using namespace std;

class Joystick_Handler: public QObject
{
    Q_OBJECT

public:
    Joystick_Handler();
//    void getMessage(QString message, int serverOrGui);

public slots:
    void changeInButtonsConfiguration(QString newConfig);
    void getButtons();

private slots:
    void messageReceive(QString message);
    void newButtonsConfig(QString newConfig);
signals:
    void sendToPi(QString);
    void sendToGUI(QString);
private:
    QString msg;
    int mapZ();
    Joystick * joyS;
    int numOfPiButtons;
    int * buttons;
};

#endif // JOYSTICK_HANDLER_H
