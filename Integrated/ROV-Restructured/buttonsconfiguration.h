#ifndef BUTTONSCONFIGURATION_H
#define BUTTONSCONFIGURATION_H
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
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
private slots:
    void timerClicked();
    void cameraClicked();
    void saveSettings();
    void cancelEdit();
    void show_hide();
private:
    QWidget * confWidget;
    QGridLayout * gridLay;
    QPushButton * timerPause_Play,*changeCamersSize;
    QPushButton * cancel,*save;
    QRadioButton *JSBttn;
    QString buttonAndRole="";
};

#endif // BUTTONSCONFIGURATION_H
