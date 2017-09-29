#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    resize(600, 500);
//    pix = QPixmap(200, 200);
    pix = QPixmap(400,400); //将画布设置大点
    pix.fill(Qt::white);

    scale =1; //设置初始放大倍数为 1，即不放大
    pushBtn = new QPushButton(this); //新建按钮对象
    pushBtn->setText(tr("zoomIn")); //设置按钮显示文本
    pushBtn->move(500,450); //设置按钮放置位置
    isDrawing = false;

    connect(pushBtn,SIGNAL(clicked()),this,SLOT(zoomIn())); //对按钮的单击事件和其槽
}

Dialog::~Dialog()
{
    delete ui;
}

#if 0
void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int x,y,w,h;
    x = lastPoint.x();
    y = lastPoint.y();
    w = endPoint.x() - x;
    h = endPoint.y() - y;
    painter.drawRect(x,y,w,h);
}
#elif 0
void Dialog::paintEvent(QPaintEvent *)
{
    int x,y,w,h;
    x = lastPoint.x();
    y = lastPoint.y();
    w = endPoint.x() - x;
    h = endPoint.y() - y;
    QPainter pp(&pix);
    pp.drawRect(x,y,w,h);
    QPainter painter(this);
    painter.drawPixmap(0,0,pix);
}
//现在虽然能画出矩形，但是却出现了无数个矩形，这不是我们想要的结果，我们希望能像第一
//步那样绘制矩形，所以我们再加入一个临时画布。
#elif 1
void Dialog::paintEvent(QPaintEvent *)
{
    int x,y,w,h;
    x = lastPoint.x();
    y = lastPoint.y();
    w = endPoint.x() - x;
    h = endPoint.y() - y;
    QPainter painter(this);
    if(isDrawing) //如果正在绘图
    {
        tempPix = pix; //将以前 pix 中的内容复制到 tempPix 中，这样实现了交互绘图
        QPainter pp(&tempPix);
        pp.drawRect(x,y,w,h);
        painter.drawPixmap(0,0,tempPix);
    }
    else
    {
        QPainter pp(&pix);
        pp.drawRect(x,y,w,h);
        painter.drawPixmap(0,0,pix);
    }
}
/*
 * 双缓冲绘图简介：
 * 根据我的理解，如果将第一步中不用画布，直接在窗口上进行绘图叫做无缓冲绘图，那么第二
 * 步中用了一个画布，将所有内容都先画到画布上，在整体绘制到窗口上，就该叫做单缓冲绘图，
 * 那个画布就是一个缓冲区。这样，第三步，用了两个画布，一个进行临时的绘图，一个进行最
 * 终的绘图，这样就叫做双缓冲绘图。
 * 我们已经看到，利用双缓冲绘图可以实现动态交互绘制。其实， Qt 中所有部件进行绘制时，
 * 都是使用的双缓冲绘图。就算是第一步中我们没有用画布， Qt 在进行自身绘制时也是使用的
 * 双缓冲绘图，所以我们刚才那么说，只是为了更好地理解双缓冲的概念。
*/
#endif

void Dialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton) //鼠标左键按下
    {
        lastPoint = event->pos();
        isDrawing = true; //正在绘图
    }
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
        isDrawing = false; //结束绘图
        update();
    }
}

void Dialog::zoomIn() //按钮单击事件的槽函数
{
    scale *=2;
    update();
}

