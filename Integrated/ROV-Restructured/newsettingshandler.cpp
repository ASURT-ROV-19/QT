#include "newsettingshandler.h"
#define buttonsInUse 10
#define piButtonsInUse 4

newSettingsHandler::newSettingsHandler()
{
    butConfig=new buttonsConfiguration;
    button = new QString [buttonsInUse];
    _button= new QString [buttonsInUse];
//    _buttons = new QString * [buttonsInUse];

    assignButtons();
    connect(butConfig,SIGNAL(sendButtonIDAndNewNumber(QString)),this,SLOT(newSettingsSelected(QString)));
    connect(this,SIGNAL(newSettingsToDisplay(QString)),butConfig,SLOT(getCurrentButtons(QString)));

}

void newSettingsHandler::assignButtons()
{
    button[0]="4";                  //upZButton;
    button[1]="2";                  //downZButton;
    button[2]="8";                  //lightOnOff;
    button[3]="0";                  //activateR;
    button[4]="3";                  //restartTimer;
    button[5]="11";                  //startMeasuringLength;
    button[6]="10";                  //ButtonsSettings;
    button[7]="1";                  //changeCamera;
    button[8]="5";                  //playPauseTimer;
    button[9]="6";                  //fullScreen;
    _button[0]="4";                  //upZButton;
    _button[1]="2";                  //downZButton;
    _button[2]="8";                  //lightOnOff;
    _button[3]="0";                  //activateR;
    _button[4]="3";                  //restartTimer;
    _button[5]="11";                  //startMeasuringLength;
    _button[6]="10";                  //ButtonsSettings;
    _button[7]="1";                  //changeCamera;
    _button[8]="5";                  //playPauseTimer;
    _button[9]="6";                  //fullScreen

}


void newSettingsHandler::newSettingsSelected(QString newConfig)
{
    //    QString buttonID=newConfig.mid(0,newConfig.indexOf(" ")+1);

        QStringList buttonID=newConfig.split(" ");
        int buttonIndex=buttonID[0].toInt();
        QString newButtonNumber=buttonID[1];
//        buttons[buttonIndex]=*buttonID[1];
        button[buttonIndex]=buttonID[1];

        //this makes us literally send the change that happened to the correct destination , later we check if this change caused another change , and if it happens  ,
//        then there we shall also send the new change , this new change is made by the program , not the user ;
        if (buttonIndex<piButtonsInUse)
            emit piSettings(newConfig);
        else if (buttonIndex<buttonsInUse)
            emit guiSettings(newConfig);

        checkForButtonsSwitch(buttonIndex,buttonID[1]);

}

void newSettingsHandler::show_hideButConfig()
{
    butConfig->show_hide();
}



//if you change any button and gave it the function of another ,this shall detect this and switch them , giving the unchanged
//button the old function of the button you changed

void newSettingsHandler::checkForButtonsSwitch(int buttonIndex, QString newNumber)
{
    QString newConfig;

    bool conflictHappended=false;
    for (int i=0;i<buttonsInUse ;i++){
        if (buttonIndex==i) continue;
        if(switchButtons(&button[buttonIndex],&_button[buttonIndex],&button[i],&_button[i])){
                conflictHappended=true;
                newConfig=QString::number(i)+" "+_button[buttonIndex];
                if (i<piButtonsInUse)
                    emit piSettings(newConfig);
                else if (i<buttonsInUse)
                    emit guiSettings(newConfig);

                break;

        }
    }
    if (!conflictHappended){
        butConfig->updateJSButtonNumber(buttonIndex,newNumber);
    }
    configuration="";
    for (int i=0;i<buttonsInUse;i++){
        _button[i]=button[i];
        configuration+=butConfig->getButtonName(i)+"     "+button[i]+"\n";
    }
    emit newSettingsToDisplay(configuration);       //want it "<buttonID> <newNumber>" , in will be decoded at receiver

}

bool newSettingsHandler::switchButtons(QString *button1, QString *old_button1, QString *button2, QString *old_button2)
{
    // if true , conflict happened here between these two buttons , we then check which was changed by the user and which is to be changed
//        by the program to compensate for the conflict ( it takes the old value of the button that was changed by the user
    if (*button1==*button2){
        if (*button1==*old_button1){   // this means that button1 wasn't changed by user , it was button1 that was changed
            butConfig->updateJSButtonNumber(*button1,*old_button2);
            *button1=*old_button2;
        }
        else {  // this means that button2 wasn't changed by user , it was button2 that was changed
            butConfig->updateJSButtonNumber(*button2,*old_button1);
            *button2=*old_button1;
        }
        return true;
    }
}

