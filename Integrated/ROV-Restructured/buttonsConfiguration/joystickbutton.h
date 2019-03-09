#ifndef JOYSTICKBUTTON_H
#define JOYSTICKBUTTON_H
#include <QPushButton>
#include <QObject>
#include <QRadioButton>
#include <QDebug>
#include <QTableWidgetItem>
namespace JS {
class joystickButton;
}

class joystickButton:public QPushButton
{
    Q_OBJECT
public:
    joystickButton();
    joystickButton(QString name,QString buttonNumber,QString id);
    void setInfo(QString name,QString buttonNumber,QString id);
    void initialDisplay();
    QString getName();
    QString getNumber();
    QString getID();
    void updateNumber(QString newNumber);

signals:
    void thisClicked(joystickButton * buttons);
    void initialDisplaySign();
public slots:
    void buttonClicked();
private:
    QString name;
    QString number;
    QString ID;
};

#endif // JOYSTICKBUTTON_H
