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

#if 0
void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawLine(0,0,100,100);
}
#else
void Dialog::paintEvent(QPaintEvent *)
{
#if 0
    QPainter painter(this);
    QPen pen; //画笔
    pen.setColor(QColor(255,0,0));
    QBrush brush(QColor(0,255,0,125)); //画刷
    painter.setPen(pen); //添加画笔
    painter.setBrush(brush); //添加画刷
    painter.drawRect(100,100,200,200); //绘制矩形
#elif 0
    QPainter painter(this);
    QPen pen(Qt::DotLine);
    QBrush brush(Qt::blue);
    brush.setStyle(Qt::HorPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(100,100,200,200);
#elif 1
    QRectF rectangle(10.0, 20.0, 80.0, 60.0); //矩形
    int startAngle = 30 * 16; //起始角度 把1度分为16份
    int spanAngle = 120 * 16; //跨越度数
    QPainter painter(this);
    painter.drawArc(rectangle, startAngle, spanAngle);
#endif
}
#endif
