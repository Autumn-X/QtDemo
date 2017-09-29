#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *)
{
#if 0 // 线性渐变
    QPainter painter(this);
    QLinearGradient linearGradient(100,150,300,150);
    //从点（ 100， 150）开始到点（ 300， 150）结束，确定一条直线
    linearGradient.setColorAt(0,Qt::red);
    linearGradient.setColorAt(0.2,Qt::black);
    linearGradient.setColorAt(0.4,Qt::yellow);
    linearGradient.setColorAt(0.6,Qt::white);
    linearGradient.setColorAt(0.8,Qt::green);
    linearGradient.setColorAt(1,Qt::blue);
    //将直线开始点设为 0，终点设为 1，然后分段设置颜色
    painter.setBrush(linearGradient);
    painter.drawRect(100,100,200,100);
    //绘制矩形，线性渐变线正好在矩形的水平中心线上
#elif 0 // 圆形渐变
    QRadialGradient radialGradient(200,100,100,200,100);
    //其中参数分别为圆形渐变的圆心（ 200， 100），半径 100，和焦点（ 200， 100）
    //这里让焦点和圆心重合，从而形成从圆心向外渐变的效果
//    QRadialGradient radialGradient(200,100,100,100,100); //改变焦点位置
    //要想改变填充的效果，只需要改变焦点的位置和渐变的颜色位置即可。
    radialGradient.setColorAt(0,Qt::black);
    radialGradient.setColorAt(1,Qt::yellow);
    //渐变从焦点向整个圆进行，焦点为起始点 0，圆的边界为 1
    QPainter painter(this);
    painter.setBrush(radialGradient);
    painter.drawEllipse(100,0,200,200);
    //绘制圆，让它正好和上面的圆形渐变的圆重合
#elif 1 //圆锥渐变
    //圆锥渐变
    QConicalGradient conicalGradient(50,50,0);
    //圆心为（ 50， 50），开始角度为 0
    conicalGradient.setColorAt(0,Qt::green);
    conicalGradient.setColorAt(1,Qt::white);
    //从圆心的 0 度角开始逆时针填充
    QPainter painter(this);
    painter.setBrush(conicalGradient);
    painter.drawEllipse(0,0,100,100);
#endif
}
