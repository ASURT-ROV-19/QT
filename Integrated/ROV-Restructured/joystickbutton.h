#ifndef JOYSTICKBUTTON_H
#define JOYSTICKBUTTON_H
#include <QPushButton>
#include <QObject>
#include <QRadioButton>
namespace JS {
class joystickButton;
}

class joystickButton:public QPushButton
{
    Q_OBJECT
public:
    joystickButton();
    joystickButton(QString name,QString buttonNumber);
    void setInfo(QString name,QString buttonNumber);
    void initialDisplay();
    QString getName();
signals:
//    void clicked();
    void initialDisplaySign();
public slots:
    void thisClicked(joystickButton ** joyButtons , joystickButton ** adminButtons , QRadioButton ** selectionButtons);
private:
    QString name;
    QString number;
};

#endif // JOYSTICKBUTTON_H
