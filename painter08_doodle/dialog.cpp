#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    resize(600, 500);
    pix = QPixmap(200, 200);
    pix.fill(Qt::white);

    scale =1; //设置初始放大倍数为 1，即不放大
    pushBtn = new QPushButton(this); //新建按钮对象
    pushBtn->setText(tr("zoomIn")); //设置按钮显示文本
    pushBtn->move(500,450); //设置按钮放置位置
    connect(pushBtn,SIGNAL(clicked()),this,SLOT(zoomIn())); //对按钮的单击事件和其槽
}

Dialog::~Dialog()
{
    delete ui;
}

#if 0
void Dialog::paintEvent(QPaintEvent *)
{
    QPainter pp(&pix);
    pp.drawLine(lastPoint,endPoint); //根据鼠标指针前后两个位置就行绘制直线
    lastPoint = endPoint; //让前一个坐标值等于后一个坐标值，这样就能实现画出连续的线
    QPainter painter(this);
    painter.drawPixmap(0,0,pix);
}
#elif 0
//3.通过上一节的学习，我们应该已经知道想让画布的内容放大有两个办法，一个是直接放大
//画布的坐标，一个是放大窗口的坐标。
//我们主要讲解放大窗口坐标。
void Dialog::paintEvent(QPaintEvent *)
{
    QPainter pp(&pix);
    pp.drawLine(lastPoint,endPoint); //根据鼠标指针前后两个位置就行绘制直线
    lastPoint = endPoint; //让前一个坐标值等于后一个坐标值，这样就能实现画出连续的线
    QPainter painter(this);
    painter.scale(scale,scale); //进行放大操作
    painter.drawPixmap(0,0,pix);
}
//运行程序。先随意画一个图形，再按下“zoomIn” 按钮，进行放大两倍。可以看到图片放大了，
//这时我们再进行绘图，绘制出的线条已经不能和鼠标指针的轨迹重合了。
//有了前面一节的知识，我们就不难理解出现这个问题的原因了。窗口的坐标扩大了，但是画布
//的坐标并没有扩大，而我们画图用的坐标值是鼠标指针的，鼠标指针又是获取的窗口的坐标值。
//现在窗口和画布的同一点的坐标并不相等，所以就出现了这样的问题
#elif 0
//其实解决办法很简单，窗口放大了多少倍，就将获得的鼠标指针的坐标值缩小多少倍就行了。
void Dialog::paintEvent(QPaintEvent *)
{
    QPainter pp(&pix);
    pp.drawLine(lastPoint/scale,endPoint/scale);
    lastPoint = endPoint;
    QPainter painter(this);
    painter.scale(scale,scale); //进行放大操作
    painter.drawPixmap(0,0,pix);
}
/*
 * 这种用改变窗口坐标大小来改变画布面积的方法，实际上是有损图片质量的。就像将一张位图
 * 放大一样，越放大越不清晰。原因就是，它的像素的个数没有变，如果将可视面积放大，那么
 * 单位面积里的像素个数就变少了，所以画质就差了。
 * 下面我们简单说说另一种方法。
*/
#elif 0
//放大画布坐标。
void Dialog::paintEvent(QPaintEvent *)
{
    QPainter pp(&pix);
    pp.scale(scale,scale);
    pp.drawLine(lastPoint/scale,endPoint/scale);
    lastPoint = endPoint;
    QPainter painter(this);
    painter.drawPixmap(0,0,pix);
}
//此时，画布中的内容并没有放大，而且画布也没有变大，不是我们想要的，所以我们再更改一下函数。
#elif 1
void Dialog::paintEvent(QPaintEvent *)
{
    if(scale!=1) //如果进行放大操作
    {
        QPixmap copyPix(pix.size()*scale); //临时画布，大小变化了 scale 倍
        QPainter pter(&copyPix);
        pter.scale(scale,scale);
        pter.drawPixmap(0,0,pix); //将以前画布上的内容复制到现在的画布上
        pix = copyPix; //将放大后的内容再复制回原来的画布上，这样只传递内容，不传递坐标系
        scale =1; //让 scale 重新置 1
    }
    QPainter pp(&pix);
    pp.scale(scale,scale);
    pp.drawLine(lastPoint/scale,endPoint/scale);
    lastPoint = endPoint;
    QPainter painter(this);
    painter.drawPixmap(0,0,pix);
}
#endif

void Dialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton) //鼠标左键按下
        lastPoint = event->pos();
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton) //鼠标左键按下的同时移动鼠标
    {
        endPoint = event->pos();
        update(); //update()函数，是进行界面重绘，执行该函数时就会执行那个重绘事件函数。
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) //鼠标左键释放
    {
        endPoint = event->pos();
        update();
    }
}

void Dialog::zoomIn() //按钮单击事件的槽函数
{
    scale *=2;
    update();
}
