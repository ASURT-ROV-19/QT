#include "gui.h"
#define buttonsInUse 7
#define piButtonsInUse 3
gui::gui(QWidget *parent)
{
//    view=new QGraphicsView();
//    view->show();
    buttons = new QString [buttonsInUse-piButtonsInUse];       // 15 is the number of buttons that are to have a specific use
//    _buttons = new QString * [15];       // 15 is the number of buttons that are to have a specific use

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

QString gui::getButtonsConfiguratuinWindow(int index)
{
//    return butConfig->getButtonName(index);
}


void gui::changeInGUI(QString button)
{


    qDebug()<<"\nbutton is "<<button;
//    const int upZButtonID=0,activateRID=1,changeCameraID=5,restartTimerID=3,playPauseTimerID=6,buttonsSettingsID=4,lightOnOffID=2;

    if (button==buttons[playPauseTimerID-piButtonsInUse])
        emit pause_play();
//
    else if(button==buttons[changeCameraID-piButtonsInUse])
        //do change in two windows sizes
    {
        toggleCamera();
    }
    else if(button==buttons[buttonsSettingsID-piButtonsInUse])
        //play or pause
    {
//        butConfig->show_hide();
    }
    else if(button==buttons[restartTimerID-piButtonsInUse])
        //restart timer
    {
        timer->restartTimer(15,0);
    }

}
//  slot to receive a QString::"<buttonID> newButtonNumber" to change local buttons value , <buttonID-piButtonsInUse> is the index if the button in the local buttons
void gui::changeInButtonsConfiguration(QString newConfig)
{
//    QString buttonID=newConfig.mid(0,newConfig.indexOf(" ")+1);

    QStringList buttonID=newConfig.split(" ");
    int buttonIndex=buttonID[0].toInt()-piButtonsInUse;
    buttons[buttonIndex]=buttonID[1];
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
    emit buttonsConfig(configuration);
}




void gui::createButtons()
{
    tmr2=new QTimer(this);
    tmr2->setInterval(2000);
    tmr2->start();
//    butConfig =new buttonsConfiguration;
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


    buttons[restartTimerID-piButtonsInUse]="3";
    buttons[buttonsSettingsID-piButtonsInUse]="4";
    buttons[changeCameraID-piButtonsInUse]="5";
    buttons[playPauseTimerID-piButtonsInUse]="6";

}


void gui::handleSignals()
{
//    connect(tmr,SIGNAL(timeout()),this,SLOT(print()));


    //THESE ARE TO SHOW OR HIDE CONF WINDOW USING MOUTH & BUTTONS OR USING JS
//    connect(this,SIGNAL(pause_play()),butConfig,SLOT(show_hide()));
//    connect(button,SIGNAL(clicked()),butConfig,SLOT(show_hide()));

//    connect(tmr2,SIGNAL(timeout()),this,SLOT(toggleCamera()));

    //THIS MEANS A NEW CONFIGURATION
//    connect(butConfig,SIGNAL(newSettings(QString)),this,SLOT(changeButtonsConfiguration(QString)));
    //TO PUASE OR PLAY TIMER USING BOTH JS OR MOUTH AND BUTTON
    connect(this,SIGNAL(pause_play()),timer,SLOT(pause_Play()));
//    connect(play_pause_button,SIGNAL(clicked()),timer,SLOT(pause_Play()));

//    connect(play_pause_button,SIGNAL(clicked()),this,SLOT(toggleCamera()));
//    connect(tmr2,SIGNAL(timeout()),this,SLOT(toggleCamera()));
//    connect(this,SIGNAL(buttonsConfig(QString)),butConfig,SLOT(getCurrentButtons(QString)));
}
