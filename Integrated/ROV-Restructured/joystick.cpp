#include "joystick.h"
#define piButtonsInUse 4
#define buttonsInUse 10
#define xAxis 0
#define yAxis 1
#define zAxis 3
#define rAxis 2
#define hat 0
#define Z_up 3
#define Z_down 1
#define light_On_Off 2
#define r_active 0


#define X this->get_x()
#define Y this->get_y()
#define Z this->get_z()
#define R this->get_r()
#define cam this->get_hat()
#define DEADZONE 4000
#define SGNFCNT 400


Joystick::Joystick()
{

    qDebug()<<"JOYSTICK CREATED";
    JoyStickInitialization();
    prev_x=prev_r=prev_y=prev_z=0;
    timer =new QTimer;
    timer->setInterval(10);
    timer->start();
//    handler = new Joystick_Handler();
    connect(timer,SIGNAL(timeout()),this,SLOT(action()));
    buttons=new int[piButtonsInUse];
    buttons[activateR]=0;       //activateR
    buttons[Z_down]=2;       //ZDown
    buttons[light_On_Off]=8;       //lightOnOffButton
    buttons[Z_up]=4;       //ZUp
}

int Joystick::get_x()
{
    return SDL_JoystickGetAxis(js,xAxis);
}

int Joystick::get_y()
{
    return -SDL_JoystickGetAxis(js,yAxis);
}
int Joystick::get_z()
{
    return -SDL_JoystickGetAxis(js,zAxis);
}
int Joystick::get_r()
{
    return activateR * SDL_JoystickGetAxis(js,rAxis);
}

int Joystick::getMapped_z()
{
    return SDL_JoystickGetAxis(js,zAxis);
}


int Joystick::get_hat()
{
    return SDL_JoystickGetHat(js,hat);
}

void Joystick::activate()
{
    js= SDL_JoystickOpen(0);
//    qDebug()<< "joystick plugged";
}

void Joystick::remove()
{
    SDL_JoystickClose(js);
    //    qDebug()<<"JS removed";
}

bool Joystick::checkIfGuiButton(int button)
{
    //True sends to GUI , while false sends to server

    for (int i=0;i<piButtonsInUse;i++){
        if (buttons[i]==button)
            return false;
    }
    return true;

}

void Joystick::buttonDown(int button)
{
    msg=QString::number(button);
    qDebug()<<button;
//the next if case decides whether we are sending to server or making a change in GUI or a joystick change
//    if(button==buttons[0]){
//        qDebug()<<"will we reverse Z direction ???????\n";
//        if (abs(mapZ())<=2){
//            (upZ==1)? (upZ=-1) : (upZ=1);
//            qDebug()<<"shall reverse Z direction\n";
//        }
//    }
    if (button==buttons[Z_up]){
        upZ=-1;
        buttonDownMessage();
    }
    else if(button==buttons[Z_down])
    {
        upZ=1;
        buttonDownMessage();
    }

    else if(button==buttons[light_On_Off]){
        light==1 ? light=0 : light=1;
        move();
    }
    else if(button==buttons[r_active])
    {
        activateR=1;
    }
    else /*if(this->checkIfGuiButton(button))*/
    {
        emit sendMsg(msg);
        qDebug()<<"message of line 113->>"<<msg;
    }

}

void Joystick::buttonUp(int button)
{
    if (button==buttons[Z_down]){
        upZ=0;
        buttonDownMessage();
    }
    else if(button==buttons[Z_up])
    {
        upZ=0;
        buttonDownMessage();
    }


    qDebug()<<"button released up is button "<<button;
    if(button==buttons[r_active])
        {
            activateR=0;
    }
}

void Joystick::changeInButtonsConfiguration(QString newConfig)
{
//    QString buttonID=newConfig.mid(0,newConfig.indexOf(" ")+1);
    QStringList buttonID=newConfig.split(" ");
    int buttonIndex=buttonID[0].toInt();
    buttons[buttonIndex]=buttonID[1].toInt();
}

int Joystick::getNumOfPiButtons()
{
    return piButtonsInUse;
}

int Joystick::getButtonNumber(int buttonIndex)
{
    return buttons[buttonIndex];
}

void Joystick::change_prev()
{
    if(abs(X-prev_x)>SGNFCNT ){

    }
    else if (abs(Y-prev_y)>SGNFCNT){

    }
    else if (abs(Z-prev_z)>SGNFCNT ){

    }
    else if (abs(R-prev_r)>SGNFCNT){

    }
}


void Joystick::JoyStickInitialization()
{

    SDL_Init(SDL_INIT_JOYSTICK);
    SDL_Init(SDL_INIT_EVERYTHING);

     if (SDL_INIT_JOYSTICK<0)
         qDebug()<<"failed to init";
     SDL_JoystickEventState(SDL_ENABLE);

/*_____________________________________________________________________________*/


     js = SDL_JoystickOpen(0);
     SDL_JoystickEventState(SDL_ENABLE);


/*_____________________________________________________________________________*/

     if (SDL_JoystickGetAttached(js)){
         qDebug() <<"attached";
     qDebug() <<"Num of buttons is : "<<SDL_JoystickNumButtons(js);
     qDebug()<<"Num of hats is : " <<SDL_JoystickNumHats(js);
     qDebug() <<"num of axes is :" <<SDL_JoystickNumAxes(js);
     qDebug() <<"num of balls is :" <<SDL_JoystickNumBalls(js); }
}

void Joystick::action()
{
    while (SDL_PollEvent(&event)){
    switch (event.type){
    case SDL_JOYAXISMOTION:
        if (abs(X-prev_x)>SGNFCNT || abs(Y-prev_y)>SGNFCNT || abs(Z-prev_z)>SGNFCNT || abs(R-prev_r)>SGNFCNT){
//            qDebug()<<"yeah , greater than SGNFCNT";
            move();
            emit sendMsg(msg);
            qDebug()<<"message of line 198->>"<<msg;
        }
        break;
    case SDL_JOYDEVICEADDED:
        this->activate();
        break;
    case SDL_JOYDEVICEREMOVED:
        this->remove();
        break;
    case SDL_JOYBUTTONDOWN:
        buttonDown(event.jbutton.button);
        break;
    case SDL_JOYBUTTONUP:
        buttonUp(event.jbutton.button);
        break;
    case SDL_JOYHATMOTION:

        move();
        emit sendMsg(msg);
        qDebug()<<"message of line 216->>"<<msg;
        break;
    default:
        break;
    }

    }
}


void Joystick::move()
{

    msg="";
    prev_x=X;
    prev_y=Y;
    prev_z=Z;
    prev_r=R;

//no mapping
//    msg+="x="+((abs(X)>DEADZONE)?QString::number(X):"0") +",";
//    msg+="y="+((abs(Y)>DEADZONE)?QString::number(Y):"0") +",";
//    msg+="z="+((abs(Z)>DEADZONE)?QString::number(Z):"0") +",";
//    msg+="r="+((abs(R)>DEADZONE)?QString::number(R):"0") +",";
//    msg+="cam="+QString::number(cam)+",";
//    msg+="light=0,";

//mapped
    msg+="x="+((abs(X)>DEADZONE)? QString::number(map(X)) : "0" )+"," ;
    msg+="y="+((abs(Y)>DEADZONE)? QString::number(map(Y)) : "0" )+"," ;
    msg+="z="+QString::number(mapZ())+",";
    msg+="r="+((abs(R)>DEADZONE)? QString::number(map(R)) : "0" )+"," ;
    msg+="cam="+QString::number(cam)+",";
    msg+="light="+QString::number(light)+",";
}


int Joystick::mapZ()
{
        return upZ * (Z*101/(32768*2)+50);
}


int Joystick::map(int x)
{
    return  x*100/32768 ;
}

void Joystick::buttonDownMessage()
{
    msg="";
    msg+="x="+QString::number(map(X))+"," ;
    msg+="y="+QString::number(map(Y))+"," ;
    msg+="z="+QString::number(mapZ())+",";
    msg+="r="+QString::number(map(R))+"," ;
    msg+="cam="+QString::number(cam)+",";
    msg+="light="+QString::number(light)+",";
    qDebug()<<msg;
    emit sendMsg(msg);
}

void Joystick::buttonUpMessage()
{
    msg="";
    msg+="x="+QString::number(map(X))+"," ;
    msg+="y="+QString::number(map(Y))+"," ;
    msg+="z=0,";
    msg+="r="+QString::number(map(R))+"," ;
    msg+="cam="+QString::number(cam)+",";
    msg+="light="+QString::number(light)+",";
    qDebug()<<msg;
    emit sendMsg(msg);

}

