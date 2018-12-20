#ifndef BUTTONSCONFIGURATION_H
#define BUTTONSCONFIGURATION_H
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QSpacerItem>
#include <QTableWidget>
#include <joystickbutton.h>
#include <math.h>
class buttonsConfiguration: public QObject
{
    Q_OBJECT
public:
    buttonsConfiguration();
    void createButtons();
    void deployButtons();
    void initialDisplay();
    void handleClicking();
    QString getButtonName(int index);
signals:
    void newSettings(QString config);
public slots:
    void show_hide();
    void getCurrentButtons(QString currentConf);
//    void selectionDisplay(joystickButton * source);
//    void initialDisplay(joystickButton * source);
private slots:
//    joystickButton ** buttons;
    void handleClicking(joystickButton * clickedButton);
    void adminButtonClicked(joystickButton * clickedButton);
private:
    QWidget * confWidget;
    QGridLayout * gridLay;
    QPushButton * timerPause_Play,*changeCamersSize,*configWindowDisp,*restart_timer;
    QPushButton * cancel,*save;
    QRadioButton *JSBttn;
    QString buttonAndRole="";
    QLabel *textLabel;
    QSpacerItem * spacer;
    QTableWidget * tableWidget;
    joystickButton ** adminButtons,**jsButtons;
    QRadioButton ** selectionButtons;
    const int adminBttns=3 , joyBttns=12 , functionBttns=12;
};

#endif // BUTTONSCONFIGURATION_H
