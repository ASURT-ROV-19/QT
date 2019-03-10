#ifndef BUTTONSCONFIGURATION_H
#define BUTTONSCONFIGURATION_H
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QSpacerItem>
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
    QString getButtonID(int index);
    void updateJSButtonNumber (int indexOfButton , QString newNumber);
    void updateJSButtonNumber (QString oldNumber , QString newNumber);
    void updateJSButtonNumber (QString oldNumber1 , QString newNumber1,QString oldNumber2 , QString newNumber2);

    ~buttonsConfiguration();
signals:
    void newSettings(QString config);
    void sendButtonIDAndNewNumber(QString message);
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
    QString buttonAndRole="";
    QString ID_newValue="";
    QLabel *textLabel;
    joystickButton ** adminButtons,         //save , cancel
    **jsButtons;                            // buttons describing a job
    QRadioButton ** selectionButtons;       // visible radio buttons on which pilot mouse clicks to select a button number

//    So pilot presses a jsButton with their hand , selection window appears on screen , pilot clicks on an adminButton
//      (say pilot wants to change how they turn light on or off) , and then mouse selects a selectionButton and save .


    const int adminBttns=3 , joyBttns=12 , functionBttns=12;
};

#endif // BUTTONSCONFIGURATION_H
