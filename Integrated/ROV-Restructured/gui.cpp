#include "gui.h"

gui::gui(QWidget *parent)
{
//    view=new QGraphicsView();
//    view->show();

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
    dummyWidget->setGeometry(0,0,115,60);

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
    int numDigits;
    if (newConfig[newConfig.length()-2]=='=')
        numDigits=1;
    else
        numDigits=2;

    check.chop(numDigits+1);
    int index=newConfig.length()-numDigits;

    if (check==butConfig->getButtonName(1)){
        cameraButton=newConfig.mid(index,numDigits);
    }
    else if (check==butConfig->getButtonName(3)){
        timerButton=newConfig.mid(index,numDigits);
    }
    else if (check==butConfig->getButtonName(0)){
        configurationButton=newConfig.mid(index,numDigits);
    }
    else if (check==butConfig->getButtonName(2)){
        restart_timer=newConfig.mid(index,numDigits);
    }

    checkForButtonsSwitch();
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


void gui::prepButtonsConfig()
{
    QString configuration;
    configuration="Camera Switch          "+cameraButton+"\n"+"Timer Play-Pause       "+timerButton+"\n"+"Configuration Window  "+configurationButton+"\n"+
            "Restart Timer           "+restart_timer;
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




void gui::handleSignals()
{
//    connect(tmr,SIGNAL(timeout()),this,SLOT(print()));


    //THESE ARE TO SHOW OR HIDE CONF WINDOW USING MOUTH & BUTTONS OR USING JS
//    connect(this,SIGNAL(pause_play()),butConfig,SLOT(show_hide()));
//    connect(button,SIGNAL(clicked()),butConfig,SLOT(show_hide()));

    connect(tmr2,SIGNAL(timeout()),this,SLOT(toggleCamera()));

    //THIS MEANS A NEW CONFIGURATION
    connect(butConfig,SIGNAL(newSettings(QString)),this,SLOT(changeButtonsConfiguration(QString)));
    //TO PUASE OR PLAY TIMER USING BOTH JS OR MOUTH AND BUTTON
    connect(this,SIGNAL(pause_play()),timer,SLOT(pause_Play()));
//    connect(play_pause_button,SIGNAL(clicked()),timer,SLOT(pause_Play()));

//    connect(play_pause_button,SIGNAL(clicked()),this,SLOT(toggleCamera()));
//    connect(tmr2,SIGNAL(timeout()),this,SLOT(toggleCamera()));
    connect(this,SIGNAL(buttonsConfig(QString)),butConfig,SLOT(getCurrentButtons(QString)));
}
