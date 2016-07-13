/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include"definition.h"
#include "widget.h"
#include "floy.h"

#include<ctime>
#include<QDebug>
#include <QTimer>
QVector<Floy*> Widget::floys;

int Widget::FloyNum=4;
int Widget::Ng_Num=2;
int Widget::MaxSpeed=50;
int Widget::BounceSpeed=20;
int Widget::RevDist=20;
int Widget::Sleep=200;

int Widget::RecombineRate=5;//meaning:5/100
bool Widget::IsRunning=false;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,0,0));
    setPalette(palette);
    setFixedSize(200, 200);
}
void Widget::init()
{
    qsrand(time(NULL));
    floys.clear();
    for(int i=0;i<FloyNum;i++){
        float x = qrand()%200;
        float y = qrand()%200;
        float vx= qrand()%50;
        float vy= qrand()%50;
        int xrev=qrand()%100;
        int yrev=qrand()%100;
        if (xrev<50)vx=-vx;
        if (yrev<50)vy=-vy;
        Floy *f=new Floy;//必须使用默认构造函数，否则不显示；？？？
        f->setFactor(x,y,vx,vy);
        floys.append(f);
    }

}
void Widget::randRecombine()//随机选择邻居
{
    int j,k,n;
    for (k=0;k<Widget::FloyNum;k++) {
            Floy* ng = Widget::floys.at(k);
            ng->neighbors.clear();
        for (j=0;j<ng->numnb;j++) {
            n =rand()%Widget::FloyNum;
            ng->neighbors.append(Widget::floys.at(n));
        }
    }
}
void Widget::animate()
{
   if(IsRunning) update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    if(IsRunning){
        int r=rand()%100;
        bool isRecombine=false;
        if(r<=RecombineRate){//随机选择邻居
            randRecombine();
            isRecombine=true;
            qDebug()<<"-------isRecombine";
        }
        painter.begin(this);
        painter.setRenderHint(QPainter::Antialiasing);
        for(int i=0;i<floys.size();++i){
            floys.at(i)->paint(&painter,isRecombine);
        }
        painter.end();



        Floy::ELAPSED++;
    }
}
void Widget::startGame(){
    init();
    qDebug()<<"FloyNum:"<<FloyNum;
    qDebug()<<"Ng_Num:"<<Ng_Num;
    qDebug()<<"MaxSpeed:"<<MaxSpeed;
    qDebug()<<"BounceSpeed:"<<BounceSpeed;
    qDebug()<<"RevDist:"<<RevDist;
    qDebug()<<"Sleep:"<<Sleep;
    IsRunning=true;
    update();
}
