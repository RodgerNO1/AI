#include "settingwidget.h"
#include"widget.h"
#include <QGridLayout>
#include<QLabel>
#include<QComboBox>
#include<QPushButton>
SettingWidget::SettingWidget(QWidget *parent) : QWidget(parent)
{
  setFixedSize(200, 400);

  QGridLayout *layout = new QGridLayout;

  QLabel *num_label=new QLabel("数量");
  num_box=new QComboBox;

  QStringList num_strs;
  num_strs<<"1"<<"2"<<"4"<<"8"<<"10"<<"15"<<"20";
  num_box->addItems(num_strs);
  num_box->setCurrentIndex(2);
  layout->addWidget(num_label, 0, 0);
  layout->addWidget(num_box, 0, 1);

  QLabel *ng_label=new QLabel("邻居数");
  ng_box=new QComboBox;
  QStringList ng_strs;
  ng_strs<<"2"<<"3"<<"4"<<"5"<<"8"<<"10";
  ng_box->addItems(ng_strs);
  ng_box->setCurrentIndex(2);
  layout->addWidget(ng_label, 1, 0);
  layout->addWidget(ng_box, 1, 1);

  QLabel *maxspeed_label=new QLabel("最大速度");
  maxspeed_box=new QComboBox;
  QStringList maxspeed_strs;
  maxspeed_strs<<"20"<<"30"<<"40"<<"50"<<"80";
  maxspeed_box->addItems(maxspeed_strs);
  maxspeed_box->setCurrentIndex(2);
  layout->addWidget(maxspeed_label, 2, 0);
  layout->addWidget(maxspeed_box, 2, 1);

  QLabel *bspeed_label=new QLabel("边界速度");
  bspeed_box=new QComboBox;
  QStringList bspeed_strs;
  bspeed_strs<<"4"<<"8"<<"16"<<"20"<<"30"<<"40";
  bspeed_box->addItems(bspeed_strs);
  bspeed_box->setCurrentIndex(2);
  layout->addWidget(bspeed_label, 3, 0);
  layout->addWidget(bspeed_box, 3, 1);

  QLabel *revdist_label=new QLabel("碰撞距离");
  revdist_box=new QComboBox;
  QStringList revdist_strs;
  revdist_strs<<"10"<<"20"<<"30"<<"40"<<"50";
  revdist_box->addItems(revdist_strs);
  revdist_box->setCurrentIndex(2);
  layout->addWidget(revdist_label, 4, 0);
  layout->addWidget(revdist_box, 4, 1);

  QLabel *time_label=new QLabel("刷新频率ms");
  time_box=new QComboBox;
  QStringList time_strs;
  time_strs<<"10"<<"20"<<"40"<<"60"<<"80"<<"100"<<"150"<<"200";
  time_box->addItems(time_strs);
  time_box->setCurrentIndex(5);
  layout->addWidget(time_label, 5, 0);
  layout->addWidget(time_box, 5, 1);

  QPushButton *ok_bt=new QPushButton("OK");
  QPushButton *reset_bt=new QPushButton("Reset");
  layout->addWidget(ok_bt, 6, 0);
  layout->addWidget(reset_bt, 6, 1);

  connect(ok_bt,SIGNAL(pressed()), this, SLOT(on_OkBt()));
  connect(reset_bt,SIGNAL(pressed()), this, SLOT(on_ResetBt()));
  setLayout(layout);

}
void SettingWidget::on_OkBt(){
    Widget::FloyNum=num_box->itemText(num_box->currentIndex()).toInt();
    Widget::Ng_Num=ng_box->itemText(ng_box->currentIndex()).toInt();
    Widget::MaxSpeed=maxspeed_box->itemText(maxspeed_box->currentIndex()).toInt();
    Widget::BounceSpeed=bspeed_box->itemText(bspeed_box->currentIndex()).toInt();
    Widget::RevDist=revdist_box->itemText(revdist_box->currentIndex()).toInt();
    Widget::Sleep=time_box->itemText(time_box->currentIndex()).toInt();

    emit restartGame();
}
void SettingWidget::on_ResetBt(){

}
