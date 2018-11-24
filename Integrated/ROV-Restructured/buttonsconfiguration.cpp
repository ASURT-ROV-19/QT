#include "buttonsconfiguration.h"



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
    confWidget->setStyleSheet("background-color: white");
    gridLay=new QGridLayout();
    confWidget->setLayout(gridLay);
    createButtons();
    deployButtons();
    handleClicking();

}

void buttonsConfiguration::createButtons()
{
    timerPause_Play=new QPushButton("Play/Pause Timer");
    changeCamersSize=new QPushButton("Change Camera");
    configWindowDisp=new QPushButton("To Display or Hide This Window");
    cancel=new QPushButton("Cancel");
    save=new QPushButton("Save");
    textLabel=new QLabel("Camera Button is 2\ntimer Button is 1\nconf Button is 0\n");
    JSBttn=new QRadioButton[6];

    for (int i=0;i<6;i++){
        JSBttn[i].setText("Joystick Button "+QString::number(i));
    }

}

void buttonsConfiguration::deployButtons()
{
    gridLay->addWidget(textLabel,3,0,1,6);
    gridLay->addWidget(timerPause_Play,0,0,1,2);
    gridLay->addWidget(changeCamersSize,0,2,1,2);
    gridLay->addWidget(configWindowDisp,0,4,1,2);

    gridLay->addWidget(cancel,2,4,1,2);
    gridLay->addWidget(save,2,1,1,3);

    for (int i=0;i<6;i++){
        gridLay->addWidget(&JSBttn[i],1,i);
    }

    initialDisplay();

}

void buttonsConfiguration::initialDisplay()
{
    cancel->hide();
    save->hide();
    timerPause_Play->show();
    changeCamersSize->show();
    configWindowDisp->show();
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
}

void buttonsConfiguration::timerClicked()
{
    buttonAndRole="timer button=";
    changeCamersSize->hide();
    configWindowDisp->hide();
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
