#include "gui.h"
#define buttonsInUse 10
#define piButtonsInUse 4
gui::gui(QWidget *parent)
{
    buttons = new QString [buttonsInUse-piButtonsInUse];
    videoDisplayer=new QGst::Ui::VideoWidget *[2];
    guiLayout=new QGridLayout(parent);          // gui layout , holding both streaming cameras
    guiItemsLayout=new QGridLayout();           //items of gui like timer , sensor label are layed out in this
    parent->setLayout(guiLayout);
    guiItemsCarryingWidget=new QWidget();       //carries gui items like timer , sensor label , and whatever , transparent and displayed over the streaming windows
    guiItemsCarryingWidget->setLayout(guiItemsLayout);
    guiItemsCarryingWidget->show();
    parent->setStyleSheet("background-color: black");
    createItems();
    assignButtons();
    handleSignals();
    guiItemsCarryingWidget->setWindowTitle("GUI Items Carrying Widget");
    guiItemsCarryingWidget->setAttribute(Qt::WA_TranslucentBackground);
    guiItemsCarryingWidget->setGeometry(0,0,150,140);
    process=new QProcess(this); 
    startLengthMeasuring();
}

gui::~gui()
{

    qDebug()<<"destroying gui instance";
    delete process;
    delete [] buttons;
//    delete timer;
    delete sensor_label;
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
    videoDisplayer[cameraNum-1]=displayWindow;
    guiLayout->addWidget(videoDisplayer[cameraNum-1],0,cameraNum-1,1,1);

    if (cameraNum==1){
        positionItems(videoDisplayer[0]);
    }
}


void gui::positionItems(QGst::Ui::VideoWidget *parent)
{
    guiItemsCarryingWidget->setParent(parent);      //initially , items are displayed over the left hand camera , which is the camera initialized first
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
        else if(button==buttons[buttonsSettingsID-piButtonsInUse])
            //play or pause
        {
            emit show_hideButConfig();
        }
        else if(button==buttons[restartTimerID-piButtonsInUse])
            //restart timer
        {
//            timer->restartTimer(15,0);
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
            positionItems(videoDisplayer[0]);       //sets display of items to be on the left hand camera
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
            positionItems(videoDisplayer[1]);
            videoDisplayer[1]->setParent(nullptr);
            videoDisplayer[0]->setParent(videoDisplayer[1]);
            guiLayout->addWidget(videoDisplayer[1],0,0,4,8);
            guiLayout->addWidget(videoDisplayer[0],0,6,1,2);
            windowSelector-=2;
        }
}

void gui::updateSensorLabel(QString depth)
{
    sensor_label->setText("depth="+depth);
}

void gui::startLengthMeasuring()
{
    process->start("python",QStringList()<<"/home/abdelrahman/ASURT/ImageProcessing/ROV19/length\ measuring/lengthMeasureStarter.py");
}




void gui::createItems()
{

//    timer=new CountDown();
//    timer->setTimer(15,0);
//    guiItemsLayout->addWidget(timer->getTimerLabel());
    sensor_label=new sensorLabel();
    guiItemsLayout->addWidget(sensor_label);
    //    timer->getTimerLabel()->setParent(window[0]);

}

void gui::assignButtons()
{
    //buttons initializations
    buttons[restartTimerID-piButtonsInUse]="3";
    buttons[buttonsSettingsID-piButtonsInUse]="10";
    buttons[changeCameraID-piButtonsInUse]="1";
    buttons[playPauseTimerID-piButtonsInUse]="5";
    buttons[startLenMeasureID-piButtonsInUse]="11";
    buttons[fullScreenID-piButtonsInUse]="6";

}


void gui::handleSignals()
{
    //TO PUASE OR PLAY TIMER USING BOTH JS OR MOUTH AND BUTTON
//    connect(this,SIGNAL(pause_play()),timer,SLOT(pause_Play()));
}
