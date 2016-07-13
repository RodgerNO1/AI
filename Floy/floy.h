#ifndef FLOY_H
#define FLOY_H
#include<QColor>
#include<QVector>
class QPainter;
class QPaintEvent;
class QColor;

class Floy
{
public:
    Floy();
    void setFactor(float x1, float y1, float vx, float vy);
    void paint(QPainter *painter, bool isRecombine);
    int dist(const Floy *ng);
    void process(bool isRecombine);
    void GetNeighbors();

    static int FLOY_CNT;
    static long ELAPSED;

    int numnb;//邻居的个数
    float acc;//苍蝇的加速度
    float acctomid;//苍蝇对中心的加速度
    float bouncespeed;//反弹到边界时候的速度
    float x;//苍蝇的X位置
    float y;//苍蝇的Y位置
    float vx;//X方向的速度
    float vy;//Y方向的速度
    float xc;//邻居中心点的位置
    float yc;//邻居中心点的位置

    QVector<Floy*> neighbors;//当前苍蝇的邻居
    QColor color;
//    QPainter *painter;

};

#endif // FLOY_H
