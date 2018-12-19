#ifndef JOYSTICK_HANDLER_H
#define JOYSTICK_HANDLER_H
#include <QTimer>
#include <string.h>
#include <QString>
#include <QDebug>

using namespace std;

class Joystick_Handler: public QObject
{
    Q_OBJECT

public:
    Joystick_Handler();
    void getMessage(QString message, int serverOrGui);

private:
    QString msg;
    int mapZ();

signals:
    void sendToServer(QString);
    void sendToGUI(QString);

};

#endif // JOYSTICK_HANDLER_H
