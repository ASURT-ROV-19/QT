#include "gui.h"

gui::gui(QWidget *parent)
{
    gridLay=new QGridLayout;
    parent->setLayout(gridLay);
    parent->setStyleSheet("background-color: lime");

    createButtons();
    handleSignals();
    createWindows();
    gridLay->addWidget(timer->getTimerLabel(),0,0);
//    gridLay->addWidget(button);
//    gridLay->addWidget(play_pause_button);
    camera=new gstream *[3];
    for (int i=0; i<3;i++) camera[i]=nullptr;
    tmr=new QTimer;
    tmr->setInterval(1000);
    connect(tmr,SIGNAL(timeout()),this,SLOT(print()));
}

QPushButton *gui::getChangingButton()
{
//    return button;
}

QGridLayout *gui::getLayout()
{
    return gridLay;
}


void gui::getCam(gstream * Camera, uint8_t cameraNum)
{
    camera[cameraNum-1]=Camera;
    gridLay->addWidget(camera[cameraNum-1]->getRenderingWindow(),0,cameraNum-1);
    window[cameraNum-1]=camera[cameraNum-1]->getRenderingWindow();
    if (cameraNum==1){
//    gridLay->removeWidget(timer->getTimerLabel());
//    timer->getTimerLabel()->setParent(camera[0]->getRenderingWindow());
    }
}

void gui::changeInGUI(QString button)
{
    if (button==timerButton)
        emit pause_play();
//
    else if(button==cameraButton)
        //do change in two windows sizes
    {
        toggleCamera();
        emit
    }
    else if(button=="3")
        //quit
    {
        qDebug()<<"shall quit";

    }
    else if(button==configurationButton)
        //play or pause
    {
        qDebug()<<"config button is "<<configurationButton;
        butConfig->show_hide();
    }

}

void gui::changeButtonsConfiguration(QString newConfig)
{

    QString check=newConfig;
    check.chop(2);
    if (check=="camera button"){
        cameraButton=newConfig[newConfig.length()-1];
    }
    else if (check=="timer button"){
        timerButton=newConfig[newConfig.length()-1];
    }
    else if (check=="config button"){
        qDebug()<<"config button shall change";
        configurationButton=newConfig[newConfig.length()-1];
    }
    qDebug()<<newConfig<<"::"<<check<<"::"<<newConfig[newConfig.length()-1];
    qDebug()<<"configuration BUTTON HAS BECOME "<<configurationButton;

    checkForButtonsSwitch();
    prepButtonsConfig();
}

void gui::createWindows()
{
   window=new QWidget *[3];
   for (int i=0; i<3;i++) window[i]=nullptr;
   window[0]==nullptr ? qDebug()<<"null":qDebug()<<"created";
}

void gui::toggleCamera()
{
    changeCamerasSizes();
    if (windowSelector==0){
        //two windows of equal size
        if (window[0]!=nullptr){
            gridLay->removeWidget(window[0]);
            gridLay->addWidget(window[0],0,0);
        g_print("Size 00\n");
        }
        if (window[1]!=nullptr){
            gridLay->removeWidget(window[1]);
            gridLay->addWidget(window[1],0,1);
        }
        windowSelector++;
        g_print("Size 00\n");
    }
    else if (windowSelector==1){
        // Window 1 becomes the main camera window

        if (window[0]!=nullptr){
            gridLay->removeWidget(window[0]);
            gridLay->addWidget(window[0],0,0,1,8);
        }
        if (window[1]!=nullptr){
            gridLay->removeWidget(window[1]);
            gridLay->addWidget(window[1],0,8,1,3);
        }
        windowSelector++;
        g_print("Size 1\n");
    }
    else if (windowSelector==2){
//        Window 2 becomes the main camera window
        if (window[0]!=nullptr){
            gridLay->removeWidget(window[0]);
            gridLay->addWidget(window[0],0,0,1,3);
        }
        if (window[1]!=nullptr){
            gridLay->removeWidget(window[1]);
            gridLay->addWidget(window[1],0,3,3,8);
        }
        windowSelector-=2;
        g_print("Size 2\n");
    }

}

void gui::print()
{
    qDebug()<<"Camera button is "<<cameraButton;
    qDebug()<<"timer button is "<<timerButton;
    qDebug()<<"Config button is "<<configurationButton;

}

void gui::prepButtonsConfig()
{
    QString configuration;
    configuration="Camera Button is "+cameraButton+"\n"+"timer Button is "+timerButton+"\n"+"conf Button is "+configurationButton+"\n";
    emit buttonsConfig(configuration);
}

void gui::changeCamerasSizes()
{
    //index1 for index of 'v' of "videoscale" , index2 is index of 'v' of "videoconvert"
    int index1[3],index2[3];

    std::string describtion[3];
    std::string temp[3];
    for (int i=0;i<2;i++){
    describtion[i]=camera[i]->getDescribtion();
    index1[i]=findStringIndex(describtion[i],"videoconvert");
    index2[i]=findStringIndex(describtion[i],"videoscale");
    describtion[i]=removeExcessPart(describtion[i],index2[i],index1[i]);
    index1[i]=findStringIndex(describtion[i],"videoconvert");
    temp[i]="videoscale ! video/x-raw,width=";
    }
    if (windowSelector==0){
        temp[0]+="800,height=600 ! ";
        temp[1]+="800,height=600 ! ";

    }
    else if (windowSelector==1){
        temp[0]+="1200,height=900 ! ";
        temp[1]+="400,height=300! ";

    }
    else if (windowSelector==2){
        temp[0]+="400,height=300 ! ";
        temp[1]+="1200,height=900 ! ";

    }

    for (int i=0;i<2;i++){
        if (index1[i]!=NULL){
            describtion[i]=describtion[i].insert(index1[i],temp[i]);
            camera[i]->manuallySetPipeline(describtion[i]);
        }
    }
    }



void gui::createButtons()
{
    butConfig =new buttonsConfiguration;
//    button=new QPushButton("Stop/Start Timer");
//    endButton=new QPushButton("Quit program");
    timer=new CountDown();
    timer->setTimer(15,0);
//    play_pause_button=new QPushButton("Play/Pause");

}



//if you change any button and gave it the function of another ,this shall detect this and switch them , giving the unchanged
//button the old function of the button you changed

void gui::checkForButtonsSwitch()
{
    if(timerButton==cameraButton){
        if (timerButton==_timerButton){
            timerButton=_cameraButton;
        }
        else{
            cameraButton=_timerButton;
        }
    }
    if(configurationButton==cameraButton){
        if (configurationButton==_configurationButton){
            configurationButton=_cameraButton;
        }
        else{
            cameraButton=_configurationButton;
        }
    }
    if(configurationButton==timerButton){
        if (configurationButton==_configurationButton){
            configurationButton=_timerButton;
        }
        else{
            timerButton=_configurationButton;
        }
    }


    _cameraButton=cameraButton;
    _timerButton=timerButton;
    _configurationButton=configurationButton;
}

int gui::findStringIndex(std::string describtion,std::string subDescribtion)
{
    int checkFlag=0;
    qDebug()<<QString::fromStdString(subDescribtion);
    for (std::size_t i=0;i<describtion.length();i++){
            checkFlag=0;
        for (std::size_t j=0;j<subDescribtion.length();j++){
                if (describtion[i+j]==subDescribtion[j]){
                    checkFlag++;
                    qDebug()<<subDescribtion[j]<<checkFlag;
                    if (checkFlag==subDescribtion.length()){
                        return (int)i;
                    }
                    continue;
                }
                else
                    break;
            }
    }
    return NULL;
}

std::string gui::removeExcessPart(std::string describtion,int startIndex,int endIndex)
{
    qDebug()<<"Start index is "<<startIndex;
    qDebug()<<"End index is "<<endIndex;

    if (startIndex!=NULL&&endIndex!=NULL){
        describtion=describtion.erase(startIndex,endIndex-startIndex);
        qDebug()<<"Gonna Erase !";
    }
    else{
        qDebug()<<"Am cool with current describtion !";
    }
    return describtion;

}




void gui::handleSignals()
{
    //THESE ARE TO SHOW OR HIDE CONF WINDOW USING MOUTH & BUTTONS OR USING JS
    connect(this,SIGNAL(pause_play()),butConfig,SLOT(show_hide()));
//    connect(button,SIGNAL(clicked()),butConfig,SLOT(show_hide()));


    //THIS MEANS A NEW CONFIGURATION
    connect(butConfig,SIGNAL(newSettings(QString)),this,SLOT(changeButtonsConfiguration(QString)));

    //TO PUASE OR PLAY TIMER USING BOTH JS OR MOUTH AND BUTTON
    connect(this,SIGNAL(pause_play()),timer,SLOT(pause_Play()));
//    connect(button,SIGNAL(clicked()),timer,SLOT(pause_Play()));

//    connect(play_pause_button,SIGNAL(clicked()),this,SLOT(toggleCamera()));

    connect(this,SIGNAL(buttonsConfig(QString)),butConfig,SLOT(getCurrentButtons(QString)));
}
