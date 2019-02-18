#ifndef NEWSETTINGSHANDLER_H
#define NEWSETTINGSHANDLER_H
#include <QObject>
#include "buttonsconfiguration.h"

class newSettingsHandler : public QObject
{
    Q_OBJECT
public:
    newSettingsHandler();
//    void setSettings(QString settings);

    void assignButtons();
    void checkForButtonsSwitch(int buttonIndex, QString newNumber);
    bool switchButtons(QString * button1,QString * old_button1,QString * button2,QString * old_button2);

public slots:
    void newSettingsSelected(QString newConfig);

signals:
    void piSettings(QString newSettings);
    void guiSettings(QString newSettings);
    void newSettingsToDisplay(QString newSettings);

private:
    buttonsConfiguration * butConfig;
    QString piConfiguration;
    QString guiConfiguration;
    QString configuration;
    QString *button;
    QString *_button;
//    QString ** _buttons;


};

#endif // NEWSETTINGSHANDLER_H


/*
    jsButtons[0]->setInfo("Z axis direction","0");
    jsButtons[1]->setInfo("R active","1");
    jsButtons[2]->setInfo("Restart Timer","2");
    jsButtons[3]->setInfo("Play/Pause Timer","3");
    jsButtons[4]->setInfo("Buttons Settings","4");
    jsButtons[5]->setInfo("Change Camera","5");
    jsButtons[6]->setInfo("light on/off","6");



*/
