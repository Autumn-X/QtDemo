#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QDebug>

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

void Dialog::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
}

void Dialog::paintEvent(QPaintEvent *)
{
#if 0
    QPainter painter(this);
    painter.drawRect(0,0,50,50);
#elif 0
    //1.我们现在进行放大操作，然后查看其坐标的变化。
    QPainter painter(this);
    painter.scale(2,2); //横纵坐标都扩大 2 倍
    painter.drawRect(0,0,50,50);
#elif 0
    //对于 QWidget， QPixmap 或 QImage 等都是绘图设备，我们都可以在其上利用 QPainter 进行绘
    //图。现在我们研究一下 QPixmap 的坐标（ QImage 与其效果相同）。
    //1.我们更改重绘事件函数如下。
    QPainter painter(this);
    QPixmap pix(200,200);
    pix.fill(Qt::red); //背景填充为红色
    painter.drawPixmap(0,0,pix);
#elif 0
    //2.我们再将函数更改如下。
    QPainter painter(this);
    QPixmap pix(200,200);
    pix.fill(Qt::red); //背景填充为红色
    painter.drawPixmap(100,100,pix);
    //这时我们从窗口的（ 100， 100）点添加该画布，那么此时我们再点击画布的右上角，其坐标会是多少呢？
    //可以看到，它是（ 100， 100），没错，这是窗口上的坐标，那么这是不是画布上的坐标呢？
#elif 0
    //3.我们接着更改函数。
    QPainter painter(this);
    QPixmap pix(200,200);
    pix.fill(Qt::red); //背景填充为红色
    QPainter pp(&pix); //新建 QPainter 类对象，在 pix 上进行绘图
    pp.drawLine(0,0,50,50); //在 pix 上的（ 0， 0）点和（ 50， 50）点之间绘制直线
    painter.drawPixmap(100,100,pix);
/*
 * 这里我们又新建了一个 QPainter 类对象 pp，其中 pp(&pix)表明， pp 所进行的绘图都是在画
 * 布 pix 上进行的。
 * 现在先说明一下：
 * QPainter painter(this) ， this 就表明了是在窗口上进行绘图，所以利用 painter 进行的绘
 * 图都是在窗口上的， painter 进行的坐标变化，是变化的窗口的坐标系；而利用 pp 进行的绘
 * 图都是在画布上进行的，如果它进行坐标变化，就是变化的画布的坐标系。
*/

    //结论
    //第一， QWidget 和 QPixmap 各有一套坐标系统，它们互不影响。可以看到，无论画布在窗口的
    //什么位置，它的坐标原点依然在左上角，为（ 0， 0）点，没有变。
    //第二，我们所得到的鼠标指针的坐标值是窗口提供的，不是画布的坐标。
#elif 0
    //4.比较下面两个例子。
    //例子一：
    QPainter painter(this);
    QPixmap pix(200,200);
    qDebug() << pix.size(); //放大前输出 pix 的大小
    pix.fill(Qt::red);
    QPainter pp(&pix);
    pp.scale(2,2); //pix 的坐标扩大 2 倍
    pp.drawLine(0,0,50,50); //在 pix 上的（ 0， 0）点和（ 50， 50）点之间绘制直线
    qDebug() << pix.size(); //放大后输出 pix 的大小
    painter.drawPixmap(0,0,pix);
#elif 1
    //例子二：
    QPainter painter(this);
    QPixmap pix(200,200);
    qDebug() << pix.size(); //放大前输出 pix 的大小
    painter.scale(2,2); //窗口坐标扩大 2 倍
    pix.fill(Qt::red);
    QPainter pp(&pix);
    pp.drawLine(0,0,50,50); //在 pix 上的（ 0， 0）点和（ 50， 50）点之间绘制直线
    qDebug() << pix.size(); //放大后输出 pix 的大小
    painter.drawPixmap(0,0,pix);
    //两个例子中都使直线的长度扩大了两倍，但是第一个例子是扩大的画布的坐标系，第二个例子
    //是扩大的窗口的坐标系，你可以看一下它们的效果。
    //仔细看一下输出，两个例子中画布的大小都没有变。

    //结论
    //所有的绘图设备都有自己的坐标系统，它们互不影响。
#endif
}
