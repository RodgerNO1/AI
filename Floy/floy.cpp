#include "floy.h"
#include "widget.h"
#include"definition.h"
#include<QPainter>
#include<QPaintEvent>
#include<ctime>
#include<QDebug>
long Floy::ELAPSED=0;
int Floy::FLOY_CNT=0;
Floy::Floy()
{
    color=QColor(0,244,0);
    FLOY_CNT++;

    numnb=Widget::Ng_Num;
    acc=10;
    acctomid=3;


}
void Floy::setFactor(float x1,float y1,float vx1,float vy1){
    x = x1;
    y = y1;
    vx=vx1;
    vy=vy1;

}
int Floy::dist(const Floy* ng){
    int d,d1,d2;
    d1=(int)(x-ng->x);
    d2=(int)(y-ng->y);
    d=d1*d1+d2*d2;
    return(d);
}
void Floy::GetNeighbors()
{
    //重新计算邻居

    neighbors.clear();
    //找到最近邻
    int i,j,k;
    QVector<int> ngDists;
    for (i=0;i<Widget::floys.size();i++) {
        Floy *ng=Widget::floys.at(i);
        ngDists.append(dist(ng));
        qDebug()<<"----ng:"<<i<<" dist:"<<ngDists.at(i);
    }

    for (i=0;i<numnb;i++) {
        int minp=0;
        for (j=0;j<ngDists.size();j++) {
            if(ngDists.at(j)==0)continue;
            if (ngDists.at(j)<ngDists.at(minp)) minp=j;
        }
        neighbors.append(Widget::floys.at(minp));
        qDebug()<<"----ngdist:"<<i<<" dist:"<<ngDists.at(minp);
		ngDists.replace(minp,0);//将当前找到的最小置零
    }

    //计算当前邻居中心位置
    xc = 0;
    yc = 0;
    for (k=0;k<numnb;k++) {
        //if (neighbors.at(k) == this) neighbors.at(k)=neighbors.at(k)->neighbors.at(0);
        xc += neighbors.at(k)->x;
        yc += neighbors.at(k)->y;
    }
    xc = xc/numnb;
    yc = yc/numnb;
}

void Floy::process(bool isRecombine){

    //重新计算邻居
    if(!isRecombine) GetNeighbors();

    int rev;
    int i;
    int d;

    rev = -1;

    for (i=0;i<numnb;i++) {

        d = dist(neighbors.at(i));
        if (d == 0)
            rev = 0;
        else if (d < Widget::RevDist) {
               rev = -1;
        }else{
                rev = 1;
        }

        if (x < neighbors.at(i)->x)
            vx += acc*rev;
        else
            vx -= acc*rev;

        if (y < neighbors.at(i)->y)
            vy += acc*rev;
        else
            vy -= acc*rev;
    }

    //中心加速度分量
    if (x < WIDTH/2) vx += acctomid;
    if (x > WIDTH/2) vx -= acctomid;
    if (y < HEIGHT/2) vy += acctomid;
    if (y > HEIGHT/2) vy -= acctomid;


    if (vx > Widget::MaxSpeed) vx = Widget::MaxSpeed;
    if (vx < -Widget::MaxSpeed) vx = -Widget::MaxSpeed;
    if (vy > Widget::MaxSpeed) vy = Widget::MaxSpeed;
    if (vy < -Widget::MaxSpeed) vy = -Widget::MaxSpeed;

    if (x < 0) vx = Widget::BounceSpeed;
    if (x > WIDTH) vx = -Widget::BounceSpeed;
    if (y < 0) vy = Widget::BounceSpeed;
    if (y > HEIGHT) vy = -Widget::BounceSpeed;

    x += vx;
    y += vy;

}

void Floy::paint(QPainter *painter,bool isRecombine)
{
    process(isRecombine);//重新计算位置与速度

    painter->save();
    painter->setBrush(color);
    painter->drawEllipse(x,y,8,8);
    painter->restore();


}
