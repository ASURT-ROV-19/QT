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
    joystickButton(QString name,QString buttonNumber);
    void setInfo(QString name,QString buttonNumber);
    void initialDisplay();
    QString getName();
    QString getNumber();
    void updateNumber(QString newNumber);
    QTableWidgetItem *getItem();
signals:
    void thisClicked(joystickButton * buttons);
    void initialDisplaySign();
public slots:
    void buttonClicked();
private:
    QString name;
    QString number;
    QTableWidgetItem *item;
};

#endif // JOYSTICKBUTTON_H
