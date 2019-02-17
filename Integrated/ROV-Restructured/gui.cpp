#include "gui.h"
#define buttonsInUse 7
gui::gui(QWidget *parent)
{
//    view=new QGraphicsView();
//    view->show();
    buttons = new QString * [15];       // 15 is the number of buttons that are to have a specific use
    _buttons = new QString * [15];       // 15 is the number of buttons that are to have a specific use

    GUIwindow=parent;
    gridLay=new QGridLayout(parent);
    parent->setLayout(gridLay);
    dummyWidget=new QWidget();
    layTimer=new QGridLayout();
    dummyWidget->setLayout(layTimer);
    dummyWidget->show();
    parent->setStyleSheet("background-color: white");
    createButtons();
    handleSignals();
    createWindows();
    dummyWidget->setWindowTitle("DUMMY WIDGET");
    dummyWidget->setAttribute(Qt::WA_TranslucentBackground);
    dummyWidget->setGeometry(0,0,150,140);

}


QGridLayout *gui::getLayout()
{
    return gridLay;
}


void gui::getCam(gstream * Camera, uint8_t cameraNum)
{
    camera[cameraNum-1]=Camera;
    videoWindow[cameraNum-1]=camera[cameraNum-1]->getRenderingVideoWindow();
    videoWindow[cameraNum-1]->show();
    videoWindow[cameraNum-1]->setWindowTitle("Gstream Video window");
    if (cameraNum==1){
//        positionItems();
    }
}

void gui::getCam(gstreamer * Camera, uint8_t cameraNum)
{
    cameraZ=new gstreamer *[3];
    cameraZ[cameraNum-1]=Camera;
//    Camera->show();
    videoDisplayer[cameraNum-1]=cameraZ[cameraNum-1]->getRenderingVideoWindow();
    gridLay->addWidget(videoDisplayer[cameraNum-1],0,cameraNum-1,1,1);

    if (cameraNum==1){
        positionItems(videoDisplayer[0]);
    }
}


void gui::positionItems(QGst::Ui::VideoWidget *parent)
{
    dummyWidget->setParent(nullptr);
    dummyWidget->setParent(parent);
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
    int numDigits,buttonIndex=-1;
    if (newConfig[newConfig.length()-2]=='=')
        numDigits=1;
    else
        numDigits=2;

    check.chop(numDigits+1);
    int index=newConfig.length()-numDigits;

    if (check==butConfig->getButtonName(1)){
        cameraButton=newConfig.mid(index,numDigits);
        butConfig->updateJSButtonNumber(1,newConfig.mid(index,numDigits));
        buttonIndex=1;
    }
    else if (check==butConfig->getButtonName(3)){
        timerButton=newConfig.mid(index,numDigits);
//        butConfig->updateJSButtonNumber(1,newConfig.mid(index,numDigits));
        buttonIndex=3;
    }
    else if (check==butConfig->getButtonName(0)){
        configurationButton=newConfig.mid(index,numDigits);
//        butConfig->updateJSButtonNumber(1,newConfig.mid(index,numDigits));
        buttonIndex=0;
    }
    else if (check==butConfig->getButtonName(2)){
        restart_timer=newConfig.mid(index,numDigits);
//        ->updateJSButtonNumber(1,newConfig.mid(index,numDigits));
        buttonIndex=2;
    }
    else if (check==butConfig->getButtonName(4)){
        upZButton=newConfig.mid(index,numDigits);
//        butConfig->updateJSButtonNumber(1,newConfig.mid(index,numDigits));
        buttonIndex=4;
    }
    else if (check==butConfig->getButtonName(5)){
        rActive=newConfig.mid(index,numDigits);
//        butConfig->updateJSButtonNumber(1,newConfig.mid(index,numDigits));
        buttonIndex=5;
    }
    else if (check==butConfig->getButtonName(6)){
        light=newConfig.mid(index,numDigits);
//        butConfig->updateJSButtonNumber(1,newConfig.mid(index,numDigits));
        buttonIndex=6;
    }
    checkForButtonsSwitch(buttonIndex,newConfig.mid(index,numDigits));
    prepButtonsConfig();
}

void gui::createWindows()
{
    camera=new gstream *[3];
    videoWindow=new QVideoWidget *[3];
    videoDisplayer=new QGst::Ui::VideoWidget *[3];

    for (int i=0; i<3;i++){
       camera[i]=nullptr;
       videoWindow[i]=nullptr;
    }
}



void gui::toggleCamera()
{
    // EQUAL SIZES
        if (windowSelector==0){
            videoDisplayer[0]->setParent(nullptr);
            videoDisplayer[1]->setParent(nullptr);
            positionItems(videoDisplayer[0]);
            gridLay->removeWidget(videoDisplayer[0]);
            gridLay->removeWidget(videoDisplayer[1]);
            gridLay->addWidget(videoDisplayer[0],0,0,1,1);
            gridLay->addWidget(videoDisplayer[1],0,1,1,1);
            windowSelector++;
        }
    //  CAMERA 1 IS MAIN
        else if (windowSelector==1){
            videoDisplayer[0]->setParent(nullptr);
            videoDisplayer[1]->setParent(nullptr);
            videoDisplayer[1]->setParent(videoDisplayer[0]);
            gridLay->removeWidget(videoDisplayer[0]);
            gridLay->removeWidget(videoDisplayer[1]);
            videoDisplayer[1]->setWindowFlags(Qt::WindowStaysOnTopHint);
            videoDisplayer[0]->setWindowFlags(Qt::WindowStaysOnBottomHint);
            gridLay->addWidget(videoDisplayer[0],0,0,4,8);
            gridLay->addWidget(videoDisplayer[1],0,6,1,2);
            windowSelector++;
        }
    //  CAMERA 2 IS MAIN
        else if (windowSelector==2){
            videoDisplayer[0]->setParent(nullptr);
            videoDisplayer[1]->setParent(nullptr);
            videoDisplayer[0]->setParent(videoDisplayer[1]);
            positionItems(videoDisplayer[1]);
            gridLay->removeWidget(videoDisplayer[1]);
            gridLay->removeWidget(videoDisplayer[0]);
//            videoDisplayer[0]->setWindowFlags(nullptr);
//            videoDisplayer[0]->setWindowFlags(nullptr);
            videoDisplayer[0]->setWindowFlags(Qt::WindowStaysOnTopHint| Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
            videoDisplayer[1]->setWindowFlags(Qt::WindowStaysOnBottomHint | Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
            gridLay->addWidget(videoDisplayer[1],0,0,4,8);
            gridLay->addWidget(videoDisplayer[0],0,6,1,2);
            windowSelector-=2;
        }
}

void gui::updateSensorLabel(QString depth)
{
    sensor_label->setText("depth="+depth);
}


void gui::prepButtonsConfig()
{

//    QString configuration;
//    configuration="Camera Switch          "+cameraButton+"\n"+"Timer Play-Pause       "+timerButton+"\n"+"Configuration Window  "+configurationButton+"\n"+
//            "Restart Timer           "+restart_timer;
    emit buttonsConfig(configuration);
}




void gui::createButtons()
{
    tmr2=new QTimer(this);
    tmr2->setInterval(2000);
    tmr2->start();
    butConfig =new buttonsConfiguration;
    button=new QPushButton("Stop/Start Timer");
    timer=new CountDown();
    timer->setTimer(15,0);
    layTimer->addWidget(timer->getTimerLabel());
    sensor_label=new sensorLabel();
    layTimer->addWidget(sensor_label);
    //    timer->getTimerLabel()->setParent(window[0]);
    play_pause_button=new QPushButton("Play/Pause");
    assignButtons();


}

void gui::assignButtons()
{


    buttons[0]=&timerButton;
    buttons[1]=&cameraButton;
    buttons[2]=&configurationButton;
    buttons[3]=&restart_timer;
    buttons[4]=&upZButton;
    buttons[5]=&rActive;
    buttons[6]=&light;
    _buttons[0]=&_timerButton;
    _buttons[1]=&_cameraButton;
    _buttons[2]=&_configurationButton;
    _buttons[3]=&_restart_timer;
    _buttons[4]=&_upZButton;
    _buttons[5]=&_rActive;
    _buttons[6]=&_light;

}



//if you change any button and gave it the function of another ,this shall detect this and switch them , giving the unchanged
//button the old function of the button you changed

void gui::checkForButtonsSwitch(int buttonIndex, QString newNumber)
{
    bool conflictHappended=false;
    for (int i=0;i<buttonsInUse-1;i++){
        for (int j=i+1;j<buttonsInUse;j++){
            if(switchButtons(buttons[i],_buttons[i],buttons[j],_buttons[j])){
                conflictHappended=true;
                break;
            }
        }
    }
    if (!conflictHappended){
        butConfig->updateJSButtonNumber(buttonIndex,newNumber);
    }
    configuration="";
    for (int i=0;i<buttonsInUse;i++){
        *_buttons[i]=*buttons[i];
        configuration+=butConfig->getButtonName(i)+"     "+*buttons[i]+"\n";
    }


//    switchButtons(&timerButton,&_timerButton,&cameraButton,&_cameraButton);
//    switchButtons(&timerButton,&_timerButton,&configurationButton,&_configurationButton);
//    switchButtons(&timerButton,&_timerButton,&restart_timer,&_restart_timer);
//    switchButtons(&configurationButton,&_configurationButton,&cameraButton,&_cameraButton);
//    switchButtons(&configurationButton,&_configurationButton,&restart_timer,&_restart_timer);
//    switchButtons(&restart_timer,&_restart_timer,&cameraButton,&_cameraButton);
//    switchButtons(&restart_timer,&_restart_timer,&cameraButton,&_cameraButton);

//    _restart_timer=restart_timer;
//    _configurationButton=configurationButton;
//    _timerButton=timerButton;
//    _cameraButton=cameraButton;
}

bool gui::switchButtons(QString *button1, QString *old_button1, QString *button2, QString *old_button2)
{
    if (*button1==*button2){
    qDebug()<<"Button1    "<<*button1<<"Button2    "<<*button2;
    qDebug()<<"Button1Old "<<*old_button1<<"Button2Old "<<*old_button2<<"\n";
        if (*button1==*old_button1){
//            wanna update JSButton->number el moshkela en dlw2ty b2a feeh 2 JSButtons el number bta3hom the same , wa7ed kan m3ah el number already , w wa7ed lessa wa5doh fo2 f function  changeButtonsConfiguration()
//            butConfig->updateJSButtonNumber(*button1,*old_button2);
            butConfig->updateJSButtonNumber(*button1,*old_button2);
            *button1=*old_button2;
        }
        else {
            butConfig->updateJSButtonNumber(*button2,*old_button1);
            *button2=*old_button1;
        }
        return true;
    }


    return false;
}




void gui::handleSignals()
{
//    connect(tmr,SIGNAL(timeout()),this,SLOT(print()));


    //THESE ARE TO SHOW OR HIDE CONF WINDOW USING MOUTH & BUTTONS OR USING JS
//    connect(this,SIGNAL(pause_play()),butConfig,SLOT(show_hide()));
//    connect(button,SIGNAL(clicked()),butConfig,SLOT(show_hide()));

//    connect(tmr2,SIGNAL(timeout()),this,SLOT(toggleCamera()));

    //THIS MEANS A NEW CONFIGURATION
    connect(butConfig,SIGNAL(newSettings(QString)),this,SLOT(changeButtonsConfiguration(QString)));
    //TO PUASE OR PLAY TIMER USING BOTH JS OR MOUTH AND BUTTON
    connect(this,SIGNAL(pause_play()),timer,SLOT(pause_Play()));
//    connect(play_pause_button,SIGNAL(clicked()),timer,SLOT(pause_Play()));

//    connect(play_pause_button,SIGNAL(clicked()),this,SLOT(toggleCamera()));
//    connect(tmr2,SIGNAL(timeout()),this,SLOT(toggleCamera()));
    connect(this,SIGNAL(buttonsConfig(QString)),butConfig,SLOT(getCurrentButtons(QString)));
}
