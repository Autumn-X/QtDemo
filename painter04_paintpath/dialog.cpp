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
#if 0
    //这里我们新建了一个 painterPath 对象，并加入了一个圆和一条线。然后绘制这个路径。
    QPainterPath path;
    path.addEllipse(100,100,50,50);
    path.lineTo(200,200);
    QPainter painter(this);
    painter.setPen(Qt::green);
    painter.setBrush(Qt::yellow);
    painter.drawPath(path);

    //上面绘制圆和直线都有对应的函数啊，为什么还要加入一个 painterPath 呢？
    //我们再添加几行代码，你就会发现它的用途了。
    QPainterPath path2;
    path2.addPath(path);
    path2.translate(100,0);
    painter.drawPath(path2);
    //这里我们又新建了一个 painterPath 对象 path2，并将以前的 path 添加到它上面，然后我们
    //更改了原点坐标为（ 100， 0），这时你发现我们复制了以前的图形。 这也就是 painterPath
    //类最主要的用途，它能保存你已经绘制好的图形。

#elif 0
    //这里我们应该注意的是绘制完一个图形后，当前的位置在哪里。
    QPainterPath path;
    path.lineTo(100,100);
    path.lineTo(200,100);
    QPainter painter(this);
    painter.drawPath(path);
    //可以看到默认是从原点（ 0， 0）开始绘图的，当画完第一条直线后，当前点应该在（ 100， 100）
    //处，然后画第二条直线。

#elif 0
    //可见画完矩形后，当前点在矩形的左上角顶点，然后从这里开始画直线。
    QPainterPath path;
    path.addRect(50,50,40,40);
    path.lineTo(200,200);
    QPainter painter(this);
    painter.drawPath(path);

#elif 1
    //我们可以自己改变当前点的位置。
    QPainterPath path;
    path.addRect(50,50,40,40);
    path.moveTo(100,100);
    path.lineTo(200,200);
    QPainter painter(this);
    painter.drawPath(path);
    //这里我们只讲解了绘制路径类最简单的应用，其实这个类很有用，利用它可以设计出很多特
    //效。有兴趣的朋友可以查看一下它的帮助。因为我们这里只是简介，所以不再深入研究。

#endif
}
