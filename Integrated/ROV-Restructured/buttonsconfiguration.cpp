#include "buttonsconfiguration.h"

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
    cancel=new QPushButton("Cancel");
    save=new QPushButton("Save");
    JSBttn=new QRadioButton[6];

    for (int i=0;i<6;i++){
        JSBttn[i].setText("Joystick Button "+QString::number(i));
    }

}

void buttonsConfiguration::deployButtons()
{
    gridLay->addWidget(timerPause_Play,0,0,1,3);
    gridLay->addWidget(changeCamersSize,0,3,1,3);
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
    for (int i=0;i<6;i++){
        JSBttn[i].hide();
    }
}

void buttonsConfiguration::handleClicking()
{
    connect(timerPause_Play,SIGNAL(clicked()),this,SLOT(timerClicked()));
    connect(changeCamersSize,SIGNAL(clicked()),this,SLOT(cameraClicked()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveSettings()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(cancelEdit()));
}

void buttonsConfiguration::timerClicked()
{
    buttonAndRole="timer button=";
    changeCamersSize->hide();
    timerPause_Play->showMenu();
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
    cancel->show();
    save->show();
    for (int i=0;i<6;i++){
        JSBttn[i].show();
    }

}

void buttonsConfiguration::saveSettings()
{
    for (int i=0;i<5;i++){
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
