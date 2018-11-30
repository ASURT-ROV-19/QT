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

class buttonsConfiguration: public QObject
{
    Q_OBJECT
public:
    buttonsConfiguration();
    void createButtons();
    void deployButtons();
    void initialDisplay();
    void handleClicking();
signals:
    void newSettings(QString config);
public slots:
    void show_hide();
    void getCurrentButtons(QString currentConf);
private slots:
    void timerClicked();
    void cameraClicked();
    void configClicked();
    void timerRestartClicked();
    void saveSettings();
    void cancelEdit();
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
};

#endif // BUTTONSCONFIGURATION_H
