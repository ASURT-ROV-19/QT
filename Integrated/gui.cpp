#include "gui.h"
#define buttonsInUse 12
#define piButtonsInUse 7

#define changeCameraID 7
#define restartTimerID 8
#define playPauseTimerID 9
#define startLenMeasureID 10
#define fullScreenID 11

gui::gui(QWidget *parent)
{
    windowSelector=0;

    guiItemsCarryingWidget=new QWidget();       //carries gui items like timer , z label , and whatever , transparent and displayed over the streaming windows
    createLayouts();
    buttons = new QString [buttonsInUse-piButtonsInUse];
    videoDisplayer=new QGst::Ui::VideoWidget *[2];
    parent->setLayout(guiLayout);
    guiItemsCarryingWidget->show();
    parent->setStyleSheet("background-color: black");
    createItems();
    assignButtons();
    handleSignals();
    guiItemsCarryingWidget->setWindowTitle("GUI Items Carrying Widget");
    guiItemsCarryingWidget->setAttribute(Qt::WA_TranslucentBackground);
    guiItemsCarryingWidget->setGeometry(0,0,200,210);
    process=new QProcess(this);
}

gui::~gui()
{

    qDebug()<<"destroying gui instance";
    delete process;
    delete [] buttons;
    delete timer;
    delete temperatureLabel;
    delete guiItemsLayout;
    for (int i=0;i<3;i++){
        delete [] videoDisplayer[i];
    }
    delete guiItemsCarryingWidget;
    delete guiLayout;
}


void gui::setDisplayWindow(QGst::Ui::VideoWidget * displayWindow, uint8_t cameraNum)
{

// here we get the display windows and make local pointers to them to manipulate them later as we like , like changing their sizes in the GUI
    videoDisplayer[cameraNum]=displayWindow;
    guiLayout->addWidget(videoDisplayer[cameraNum],0,cameraNum,1,1);
    setCameraWindowLayout(cameraNum);
    if (cameraNum==0){
        positionItems(camsLayout[cameraNum]);
    }
    else
        toggleCamera();
}


void gui::positionItems(QGridLayout *parent)
{
    parent->addWidget(guiItemsCarryingWidget,0,0,1,1);      //initially , items are displayed over the left hand camera , which is the camera initialized first
    //    parent->addItem(verticalSpacer,1,0,1,4);
}

void gui::setEndoscopeCamera(gstreamer *endoscopeCamera)
{
    this->endoscopeCamera=endoscopeCamera;
    endoscopeCamera->getRenderingVideoWindow()->hide();
}


void gui::changeInGUI(QString button)
{
   //    QString upZButton="0",activateR="1",lightOnOff="2",restartTimer="3",buttonsSettings="4",changeCamera="5",playPauseTimer="6";

        if(button==buttons[startLenMeasureID-piButtonsInUse])
        {
            qDebug()<<"will enter startMeasuring Function";
            startLengthMeasuring();
        }
        if (button==buttons[playPauseTimerID-piButtonsInUse])
            emit pause_play();
    //
        else if(button==buttons[changeCameraID-piButtonsInUse])
            //do change in two windows sizes
        {
            toggleCamera();
        }
//        else if(button==buttons[buttonsSettingsID-piButtonsInUse])
//            //play or pause
//        {
//            emit show_hideButConfig();
//        }
        else if(button==buttons[restartTimerID-piButtonsInUse])
            //restart timer
        {
            timer->restartTimer(15,0);
        }
    else if(button==buttons[fullScreenID-piButtonsInUse])
        //toggle screen between full and normal
    {
        emit guiSizeChange();
    }
}
//  slot to receive a QString::"<buttonID> newButtonNumber" to change local buttons value , <buttonID-piButtonsInUse> is the index if the button in the local buttons
void gui::changeInButtonsConfiguration(QString newConfig)
{
    //buttonInfo is : <"buttonID buttonNumber">
    QStringList buttonInfo=newConfig.split(" ");
    int buttonIndex=buttonInfo[0].toInt()-piButtonsInUse;
    buttons[buttonIndex]=buttonInfo[1];
}


void gui::toggleCamera()
{

    qDebug()<<"toggling camera";
    // EQUAL SIZES
        if (windowSelector==0){
            positionItems(camsLayout[0]);       //sets display of items to be on the left hand camera
//            videoDisplayer[0]->setParent(nullptr);
//            videoDisplayer[1]->setParent(nullptr);
            guiLayout->addWidget(videoDisplayer[0],0,0,1,1);
            guiLayout->addWidget(videoDisplayer[1],0,1,1,1);
            windowSelector++;
        }
    //  CAMERA 1 IS MAIN
        else if (windowSelector==1){
            videoDisplayer[0]->setParent(nullptr);
            videoDisplayer[1]->setParent(videoDisplayer[0]);
            guiLayout->addWidget(videoDisplayer[0],0,0,4,8);
            guiLayout->addWidget(videoDisplayer[1],0,6,1,2);
            windowSelector++;
        }
    //  CAMERA 2 IS MAIN
        else if (windowSelector==2){
            positionItems(camsLayout[1]);
            videoDisplayer[1]->setParent(nullptr);
            videoDisplayer[0]->setParent(videoDisplayer[1]);
            guiLayout->addWidget(videoDisplayer[1],0,0,4,8);
            guiLayout->addWidget(videoDisplayer[0],0,6,1,2);
            windowSelector-=2;
        }
}

void gui::receiveFromPi(QString temp)
{
    temperatureLabel->setText("Temperature="+temp);
}

void gui::updateZdirection(QString direction)
{
    zDirection->setText("Z "+direction);
}

void gui::createLayouts()
{
    guiLayout=new QGridLayout();          // gui layout , holding both streaming cameras
    guiItemsLayout=new QGridLayout();           //items of gui like timer , Zdirection label are layed out in this
    guiItemsCarryingWidget->setLayout(guiItemsLayout);
    camsLayout=new QGridLayout * [2];
    camsLayout[0]=new QGridLayout();
    camsLayout[1]=new QGridLayout();
    verticalSpacer=new QSpacerItem(1,1,QSizePolicy::Preferred,QSizePolicy::Expanding);

}

void gui::setCameraWindowLayout(int cameraIndex)
{
    videoDisplayer[cameraIndex]->setLayout(camsLayout[cameraIndex]);
}

void gui::startLengthMeasuring()
{
    process->start("python",QStringList()<<"/home/abdelrahman/ASURT/ImageProcessing/ROV19/length\ measuring/lengthMeasureStarter.py");
}

void gui::toggleEndoFullScreen()
{
    endoscopeCamera->getRenderingVideoWindow()->isFullScreen() ? endoscopeCamera->getRenderingVideoWindow()->showNormal() : endoscopeCamera->getRenderingVideoWindow()->setWindowState(Qt::WindowFullScreen);

}




void gui::createItems()
{

    timer=new CountDown();
    timer->setTimer(15,0);
    guiItemsLayout->addWidget(timer->getTimerLabel(),0,0,1,1);
    temperatureLabel=new QLabel("temperature");
    temperatureLabel->hide();
    temperatureLabel->setGeometry(300,300,300,300);
    temperatureLabel->setStyleSheet("QLabel{color: red ;  font-size: 30px; background-color= white}");
    temperatureLabel->setAlignment(Qt::AlignCenter);
    zDirection=new transparentLabel("orange","25",Qt::AlignmentFlag::AlignTop,Qt::AlignmentFlag::AlignLeft);
    zDirection->setGeometry(0,0,200,60);
    guiItemsLayout->addWidget(zDirection,2,0,1,1);
    updateZdirection("-");
    guiItemsLayout->addItem(verticalSpacer,3,0,1,4);
    cameraLabel=new transparentLabel[2];
    cameraLabel[0].setText("cam1");
    cameraLabel[1].setText("cam2");
    camsLayout[0]->addWidget(&cameraLabel[0],3,1,1,1);
    camsLayout[1]->addWidget(&cameraLabel[1],3,1,1,1);

}

void gui::assignButtons()
{
    //buttons initializations
    buttons[restartTimerID-piButtonsInUse]="10";
//    buttons[buttonsSettingsID-piButtonsInUse]="11111111111";            //can't come true
    buttons[changeCameraID-piButtonsInUse]="1";
    buttons[playPauseTimerID-piButtonsInUse]="9";
    buttons[startLenMeasureID-piButtonsInUse]="11";
    buttons[fullScreenID-piButtonsInUse]="6";
//0-1-2-3-4-5-6-7-8-9-10-11

}


void gui::handleSignals()
{
    //TO PUASE OR PLAY TIMER USING BOTH JS OR MOUTH AND BUTTON
    connect(this,SIGNAL(pause_play()),timer,SLOT(pause_Play()));

}

void gui::showOrHideEndoscopeCamera()
{
    if(endoscopeCamera->getRenderingVideoWindow()->isHidden()){
        endoscopeCamera->getRenderingVideoWindow()->show();
    }
    else
        endoscopeCamera->getRenderingVideoWindow()->hide() ;
}

void gui::showOrHideTempLabel()
{
    if(temperatureLabel->isHidden()){
        temperatureLabel->show();
    }
    else
        temperatureLabel->hide() ;

}
