#include "buttonsconfiguration.h"
#include <QDebug>


/*
    PROCEDURE TO ADD A BUTTON TO THE CHANGING BUTTONS:
    1-ADD A RESPRESENTATIVE BUTTON AND SLOT FOR IT HERE
    2-CONNECT THE BUTTON CLICKING AND THE SLOT
    3-IN THE SLOT , SET A SUITABLE MESSAGE THAT CONTAINS YOUR DESIRED JS BUTTON
    4-REMEMBER THE MESSAGE

    THEN IN GUI CLASS:
    5-CREATE A QSTRING IN IT
    6-GOTO CHANGE_IN_GUI FUNCNTION , WITHIN IT , ADD A CONDITION IF BUTTON==YOUR RECENTLY CREATED STRING IN STEP 5 , IF IT HAPPENS
        WHAT YOU HAPPEN SHALL BE PERFORMED
    7-GOTO CHANGE_BUTTONS_CONFIGURATION FUNCTION AND ADD YOUR CONDITION , IF CHECK== YOUR MESSAGE FROM STEPS 3&4 , THEN YOUR STEP 5
        QSTRING SHALL BECOME newConfig[newConfig.length()-1];

    8-DONE



*/



buttonsConfiguration::buttonsConfiguration()
{
    confWidget=new QWidget();
    confWidget->setGeometry(200,200,800,600);
    confWidget->setStyleSheet("background-color: orange ;");
    confWidget->setWindowTitle("Joystick Buttons Configuration");
    confWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
    gridLay=new QGridLayout();
    confWidget->setLayout(gridLay);
    createButtons();
    deployButtons();
    handleClicking();
    spacer=new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Expanding);

}

void buttonsConfiguration::createButtons()
{

//    buttons=new joystickButton * [20];
//    buttons[0]->setInfo("Configurations","0");
//    buttons[1]->setInfo("Switch View","2");
//    buttons[2]->setInfo("Timer Restart","3");

    restart_timer=new QPushButton("Restart Timer");
    timerPause_Play=new QPushButton("Play/Pause Timer");
    changeCamersSize=new QPushButton("Change Camera");
    configWindowDisp=new QPushButton("To Display or Hide This Window");
    cancel=new QPushButton("Cancel");
    save=new QPushButton("Save");
    textLabel=new QLabel("Camera Switch:         2\nTimer Play-Pause       1\nConfiguration Window  0\nRestart Timer           3");
    JSBttn=new QRadioButton[12];
//    save->setStyleSheet(" border: 1px solid white  ; ");
    for (int i=0;i<12;i++){
        JSBttn[i].setText("Joystick Button "+QString::number(i));
    }

}

void buttonsConfiguration::deployButtons()
{
    textLabel->setStyleSheet("QLabel{color: black ;  font-size: 20px; background-color: orange ; font:arial,helvetica; }");
//    textLabel->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 white, stop: 0.4 gray, stop:1 green)");
    gridLay->addWidget(timerPause_Play,1,0,1,2);
    gridLay->addWidget(changeCamersSize,1,2,1,2);
    gridLay->addWidget(configWindowDisp,1,4,1,2);
    gridLay->addWidget(restart_timer,2,0,1,2);

    gridLay->addWidget(textLabel,0,2,1,2);
    textLabel->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    gridLay->addWidget(save,6,4,1,1);
    gridLay->addWidget(cancel,6,5,1,1);
    gridLay->setVerticalSpacing(50);
    gridLay->setMargin(50);
//    textLabel->setStyleSheet("background-color: grey;");
//    textLabel->setMaximumWidth(300);
//    textLabel->setMaximumHeight(200);
    int j=-3;
    for (int i=0;i<6;i++){
        i<3 ? gridLay->addWidget(&JSBttn[i],3,2*i,1,2) : gridLay->addWidget(&JSBttn[i],4,2*j,1,2);
        JSBttn[i].setStyleSheet("color: black ;font-size: 20px; background-color: orange ; font:arial,helvetica;");
        JSBttn[i].setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
        j++;
    }

    initialDisplay();

}

void buttonsConfiguration::initialDisplay()
{

    confWidget->show();
    cancel->hide();
    save->hide();
    timerPause_Play->show();
    changeCamersSize->show();
    configWindowDisp->show();
    restart_timer->show();
    for (int i=0;i<6;i++){
        JSBttn[i].hide();
    }
}

void buttonsConfiguration::handleClicking()
{
    connect(timerPause_Play,SIGNAL(clicked()),this,SLOT(timerClicked()));
    connect(changeCamersSize,SIGNAL(clicked()),this,SLOT(cameraClicked()));
    connect(configWindowDisp,SIGNAL(clicked()),this,SLOT(configClicked()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveSettings()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(cancelEdit()));
    connect(restart_timer,SIGNAL(clicked()),this,SLOT(timerRestartClicked()));

}

void buttonsConfiguration::timerClicked()
{
    buttonAndRole="timer button=";
    changeCamersSize->hide();
    configWindowDisp->hide();
    restart_timer->hide();
    cancel->show();
    save->show();

    for (int i=0;i<6;i++){
        JSBttn[i].show();
    }
}

void buttonsConfiguration::cameraClicked()
{

    buttonAndRole="camera button=";
    timerPause_Play->hide();
    configWindowDisp->hide();
    restart_timer->hide();
    cancel->show();
    save->show();
    for (int i=0;i<6;i++){
        JSBttn[i].show();
    }

}

void buttonsConfiguration::configClicked()
{

    buttonAndRole="config button=";
    timerPause_Play->hide();
    changeCamersSize->hide();
    restart_timer->hide();
    cancel->show();
    save->show();
    for (int i=0;i<6;i++){
        JSBttn[i].show();
    }
}

void buttonsConfiguration::timerRestartClicked()
{
    buttonAndRole="timerRestart button=";
    timerPause_Play->hide();
    changeCamersSize->hide();
    configWindowDisp->hide();
    cancel->show();
    save->show();
    for (int i=0;i<6;i++){
        JSBttn[i].show();
    }
}

void buttonsConfiguration::saveSettings()
{
    for (int i=0;i<6;i++){
        if(JSBttn[i].isChecked()){
            buttonAndRole+=QString::number(i);
            break;
        }
    }

    emit newSettings(buttonAndRole);
    buttonAndRole="";
    initialDisplay();
}

void buttonsConfiguration::cancelEdit()
{
    buttonAndRole="";
    initialDisplay();
}

void buttonsConfiguration::show_hide()
{
    confWidget->isHidden() ? confWidget->show() : confWidget->hide();
}

void buttonsConfiguration::getCurrentButtons(QString currentConf)
{
    textLabel->setText(currentConf);
}
