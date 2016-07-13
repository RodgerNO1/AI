/****************************************************************************
**
**
****************************************************************************/

#include "widget.h"
#include "window.h"
#include"settingwidget.h"
#include <QGridLayout>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include <QPushButton>
#include <QTimer>


Window::Window()
{
    setWindowTitle(tr("Floy"));

    gameview = new Widget(this);
    setting_wiget=new SettingWidget;
    start_bt = new QPushButton(tr("Start"));
    pause_bt = new QPushButton(tr("Pause"));
    setting_bt = new QPushButton(tr("Setting"));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(gameview);
    vlayout->setAlignment(gameview,Qt::AlignHCenter);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(start_bt);
    hlayout->addWidget(pause_bt);
    hlayout->addWidget(setting_bt);

    vlayout->addLayout(hlayout);
    setLayout(vlayout);

    timer=NULL;//初始化定时器

    connect(start_bt,SIGNAL(pressed()), this, SLOT(onStartBt()));
    connect(pause_bt,SIGNAL(pressed()), this, SLOT(onPauseBt()));
    connect(setting_bt,SIGNAL(pressed()), setting_wiget, SLOT(show()));
    connect(setting_wiget,SIGNAL(restartGame()), this, SLOT(onStartBt()));
}

void Window::onStartBt(){
    gameview->IsRunning=true;
    gameview->startGame();
    //定时器
    if(timer){
       timer->stop();
       delete timer;
    }
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, gameview, &Widget::animate);
    timer->start(gameview->Sleep);
}
void Window::onPauseBt(){
    if(gameview->IsRunning){
        gameview->IsRunning=false;
        pause_bt->setText("Continue");
    }else{
        gameview->IsRunning=true;
        pause_bt->setText("Pause");
    }

}
