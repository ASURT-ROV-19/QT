#include "gui.h"

gui::gui(QWidget *parent)
{
    GUIwindow=parent;
    gridLay=new QGridLayout;
    parent->setLayout(gridLay);
    parent->setStyleSheet("background-color: white");
    createButtons();
    handleSignals();
    createWindows();
//    gridLay->addWidget(button);
//    gridLay->addWidget(play_pause_button);
    tmr=new QTimer;
    tmr->setInterval(1000);

}


QGridLayout *gui::getLayout()
{
    return gridLay;
}


void gui::getCam(gstream * Camera, uint8_t cameraNum)
{
    camera[cameraNum-1]=Camera;
    window[cameraNum-1]=camera[cameraNum-1]->getRenderingWindow();
    gridLay->addWidget(window[cameraNum-1],0,cameraNum-1);
//    gridLay->addWidget(timer->getTimerLabel(),0,0);
//    timer->getTimerLabel()->setParent(window[0]);
//    timer->getTimerLabel()->setGeometry(0,0,100,40);
    timer->getTimerLabel()->setParent(window[0]);
    timer->getTimerLabel()->setGeometry(0,0,100,40);
    window[0]->setStyleSheet("background-color:white;");

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

    }
    else if(button==restart_timer)
        //restart timer
    {
        timer->restartTimer(15,0);
    }
    else if(button==configurationButton)
        //play or pause
    {
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
        configurationButton=newConfig[newConfig.length()-1];
    }
    else if (check=="timerRestart button"){
        restart_timer=newConfig[newConfig.length()-1];
    }

    checkForButtonsSwitch();
    prepButtonsConfig();
}

void gui::createWindows()
{
    camera=new gstream *[3];
    window=new QWidget *[3];

   for (int i=0; i<3;i++){
       camera[i]=nullptr;
       window[i]=nullptr;
    }
}

void gui::toggleCamera()
{
//    changeCamerasSizes();
    if (windowSelector==0){

//        timer->getTimerLabel()->setParent(nullptr);
        timer->getTimerLabel()->setParent(window[0]);
        timer->getTimerLabel()->setGeometry(0,0,100,40);

        window[1]->setParent(nullptr);
        //two windows of equal size
        if (window[0]!=nullptr){
            gridLay->removeWidget(window[0]);
            gridLay->addWidget(window[0],0,0);
//        g_print("Size 00\n");
        }
        if (window[1]!=nullptr){
            gridLay->removeWidget(window[1]);
            gridLay->addWidget(window[1],0,1);
        }
        windowSelector++;
        g_print("Size 00\n");
        timer->getTimerLabel()->setParent(window[0]);
        timer->getTimerLabel()->show();
//        timer->getTimerLabel()->setGeometry(0,0,100,40);

    }
    else if (windowSelector==1){
        // Window 1 becomes the main camera window
        window[1]->setParent(window[0]);
        if (window[0]!=nullptr){
            gridLay->removeWidget(window[0]);
            gridLay->addWidget(window[0],0,0,3,8);
        }
        if (window[1]!=nullptr){
            gridLay->removeWidget(window[1]);
            gridLay->addWidget(window[1],0,5,1,3);
        }
        windowSelector++;
        g_print("Size 1\n");
    }
    else if (windowSelector==2){
//        Window 2 becomes the main camera window
        window[0]->setParent(window[1]);

        if (window[1]!=nullptr){
            gridLay->removeWidget(window[1]);
            gridLay->addWidget(window[1],0,0,3,8);
        }
        if (window[0]!=nullptr){
            gridLay->removeWidget(window[0]);
            gridLay->addWidget(window[0],0,5,1,3);
        }
        windowSelector-=2;
//        timer->getTimerLabel()->setParent(nullptr);
        timer->getTimerLabel()->setParent(window[1]);
        timer->getTimerLabel()->show();
        timer->getTimerLabel()->setGeometry(0,0,100,40);

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
    configuration="Camera Switch          "+cameraButton+"\n"+"Timer Play-Pause       "+timerButton+"\n"+"Configuration Window  "+configurationButton+"\n"+
            "Restart Timer           "+restart_timer;
    emit buttonsConfig(configuration);
}

//void gui::changeCamerasSizes()
//{
//    //index1 for index of 'v' of "videoscale" , index2 is index of 'v' of "videoconvert"
//    int index1[3],index2[3];

//    std::string describtion[3];
//    std::string temp[3];
//    for (int i=0;i<2;i++){
//    describtion[i]=camera[i]->getDescribtion();
//    index1[i]=findStringIndex(describtion[i],"videoconvert");
//    index2[i]=findStringIndex(describtion[i],"videoscale");
//    describtion[i]=removeExcessPart(describtion[i],index2[i],index1[i]);
//    index1[i]=findStringIndex(describtion[i],"videoconvert");
//    temp[i]="videoscale ! video/x-raw,width=";
//    }
//    if (windowSelector==0){
//        temp[0]+="945,height=995 ! ";
//        temp[1]+="945,height=995 ! ";
//        qDebug()<<window[0]->width()<<" * "<<window[1]->height();
//    }
//    else if (windowSelector==1){
//        temp[0]+="1378,height=995 ! ";
//        temp[1]+="100,height=100 ! ";
//        qDebug()<<window[0]->width()<<" * "<<window[1]->height();
//        int dummy=findStringIndex(describtion[1],"xvimagesink");
////        qDebug()<<dummy;
////        describtion[1]=describtion[1].erase(dummy,1);

//    }
//    else if (windowSelector==2){
//        temp[0]+="524,height=500 ! ";
//        temp[1]+="1200,height=900 ! ";
//        qDebug()<<window[0]->width()<<" * "<<window[1]->height();

//    }

//    for (int i=0;i<2;i++){
//        if (index1[i]!=NULL){
//            describtion[i]=describtion[i].insert(index1[i],temp[i]);
//            camera[i]->manuallySetPipeline(describtion[i]);
//        }
//    }

//}



void gui::createButtons()
{
    tmr2=new QTimer(this);
    tmr2->setInterval(3000);
    tmr2->start();
    butConfig =new buttonsConfiguration;
    button=new QPushButton("Stop/Start Timer");
//    endButton=new QPushButton("Quit program");
    timer=new CountDown();
    timer->setTimer(15,0);
//    timer->getTimerLabel()->setParent(window[0]);
    play_pause_button=new QPushButton("Play/Pause");

}



//if you change any button and gave it the function of another ,this shall detect this and switch them , giving the unchanged
//button the old function of the button you changed

void gui::checkForButtonsSwitch()
{

    switchButtons(&timerButton,&_timerButton,&cameraButton,&_cameraButton);
    switchButtons(&timerButton,&_timerButton,&configurationButton,&_configurationButton);
    switchButtons(&timerButton,&_timerButton,&restart_timer,&_restart_timer);
    switchButtons(&configurationButton,&_configurationButton,&cameraButton,&_cameraButton);
    switchButtons(&configurationButton,&_configurationButton,&restart_timer,&_restart_timer);
    switchButtons(&restart_timer,&_restart_timer,&cameraButton,&_cameraButton);
    switchButtons(&restart_timer,&_restart_timer,&cameraButton,&_cameraButton);

    _restart_timer=restart_timer;
    _configurationButton=configurationButton;
    _timerButton=timerButton;
    _cameraButton=cameraButton;
}

void gui::switchButtons(QString *button1, QString *old_button1, QString *button2, QString *old_button2)
{
    QString temp;

    if (*button1==*button2){
    qDebug()<<"Button1    "<<*button1<<"Button2    "<<*button2;
    qDebug()<<"Button1Old "<<*old_button1<<"Button2Old "<<*old_button2;
        if (*button1==*old_button1){
            temp=*button1;
            *button1=*old_button2;
        }
        else {
            *button2=*old_button1;
        }
    }

}

//int gui::findStringIndex(std::string describtion,std::string subDescribtion)
//{
//    int checkFlag=0;
//       for (std::size_t i=0;i<describtion.length();i++){
//            checkFlag=0;
//        for (std::size_t j=0;j<subDescribtion.length();j++){
//                if (describtion[i+j]==subDescribtion[j]){
//                    checkFlag++;
//                    if (checkFlag==subDescribtion.length()){
//                        return (int)i;
//                    }
//                    continue;
//                }
//                else
//                    break;
//            }
//    }
//       return NULL;
//}






void gui::handleSignals()
{
//    connect(tmr,SIGNAL(timeout()),this,SLOT(print()));


    //THESE ARE TO SHOW OR HIDE CONF WINDOW USING MOUTH & BUTTONS OR USING JS
//    connect(this,SIGNAL(pause_play()),butConfig,SLOT(show_hide()));
//    connect(button,SIGNAL(clicked()),butConfig,SLOT(show_hide()));


    //THIS MEANS A NEW CONFIGURATION
    connect(butConfig,SIGNAL(newSettings(QString)),this,SLOT(changeButtonsConfiguration(QString)));

    //TO PUASE OR PLAY TIMER USING BOTH JS OR MOUTH AND BUTTON
    connect(this,SIGNAL(pause_play()),timer,SLOT(pause_Play()));
//    connect(play_pause_button,SIGNAL(clicked()),timer,SLOT(pause_Play()));

//    connect(play_pause_button,SIGNAL(clicked()),this,SLOT(toggleCamera()));
//    connect(tmr2,SIGNAL(timeout()),this,SLOT(toggleCamera()));
    connect(this,SIGNAL(buttonsConfig(QString)),butConfig,SLOT(getCurrentButtons(QString)));
}
