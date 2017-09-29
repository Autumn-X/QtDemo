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

/*
 *     前面一节我们讲解了图片的显示，其中很多都用到了坐标的变化，这一节我们简单讲一下 Qt
 * 的坐标系统，其实也还是主要讲上一节的那几个函数。这里我们先讲解一下 Qt 的坐标系，然
 * 后讲解那几个函数，它们分别是：
 * translate()函数，进行平移变换；
 * scale()函数，进行比例变换；
 * rotate()函数，进行旋转变换；
 * shear()函数，进行扭曲变换。
 *     最后介绍两个有用的函数 save()和 restore()，利用它们来保存和弹出坐标系的状态，从而
 * 实现快速利用几个变换来绘图。
 *     坐标系变换是利用变换矩阵来进行的，我们可以利用 QTransform 类来设置变换矩阵，因为一
 * 般我们不需要进行更改，所以这里不在涉及。下面我们只是对坐标系的平移，缩放，旋转，扭
 * 曲等应用进行介绍。
 */
void Dialog::paintEvent(QPaintEvent *)
{
#if 0
    QPainter painter(this);
    painter.setBrush(Qt::red);
    painter.drawRect(0,0,100,100);
    painter.setBrush(Qt::yellow);
    painter.drawRect(-50,-50,100,100);
    //我们先在原点（ 0， 0）绘制了一个长宽都是 100 像素的红色矩形，又在（ -50， -50）点绘制了
    //一个同样大小的黄色矩形。可以看到，我们只能看到黄色矩形的一部分。
#elif 0
    //1.利用 translate()函数进行平移变换。
    QPainter painter(this);
    painter.setBrush(Qt::yellow);
    painter.drawRect(0,0,50,50);
    painter.translate(100,100); //将点（ 100， 100）设为原点
    painter.setBrush(Qt::red);
    painter.drawRect(0,0,50,50);
    painter.translate(-100,-100);
    painter.drawLine(0,0,20,20);
#elif 0
    //2.利用 scale()函数进行比例变换，实现缩放效果。
    QPainter painter(this);
    painter.setBrush(Qt::yellow);
    painter.drawRect(0,0,100,100);
    painter.scale(2,2); //放大两倍
    painter.setBrush(Qt::red);
    painter.drawRect(50,50,50,50);
#elif 0
    //3.利用 shear()函数就行扭曲变换。
    QPainter painter(this);
    painter.setBrush(Qt::yellow);
    painter.drawRect(0,0,50,50);
    painter.shear(0,1); //纵向扭曲变形
    painter.setBrush(Qt::red);
    painter.drawRect(50,0,50,50);
#elif 0
    //4.利用 rotate()函数进行比例变换，实现缩放效果。
    QPainter painter(this);
    painter.drawLine(0,0,100,0);
    painter.rotate(30); //以原点为中心，顺时针旋转 30 度
    painter.drawLine(0,0,100,0);
    painter.translate(100,100);
    painter.rotate(30);
    painter.drawLine(0,0,100,0);
#elif 0
    //因为默认的 rotate()函数是以原点为中心进行顺时针旋转的，所以我们要想使其以其他点为
    //中心进行旋转，就要先进行原点的变换。这里的 painter.translate(100,100)将（ 100， 100）
    //设置为新的原点，想让直线以其为中心进行旋转，可是你已经发现效果并非如此。是什么原因
    //呢？我们添加一条语句，如下：
    QPainter painter(this);
    painter.drawLine(0,0,100,0);
    painter.rotate(30); //以原点为中心，顺时针旋转 30 度
    painter.drawLine(0,0,100,0);
    painter.rotate(-30); //添加的语句
    painter.translate(100,100);
    painter.rotate(30);
    painter.drawLine(0,0,100,0);
    //这时就是我们想要的效果了。我们加的一句代码为 painter.rotate(-30)，这是因为前面已经
    //将坐标旋转了 30 度，我们需要将其再旋转回去，才能是以前正常的坐标系统。不光这个函数
    //如此，这里介绍的这几个函数均如此，所以很容易出错。下面我们将利用两个函数来很好的解
    //决这个问题。
#elif 1
    //三、坐标系状态的保护。
    //我们可以先利用 save()函数来保存坐标系现在的状态，然后进行变换操作，操作完之后，再
    //用 restore()函数将以前的坐标系状态恢复，其实就是一个入栈和出栈的操作。
    QPainter painter(this);
    painter.save(); //保存坐标系状态
    painter.translate(100,100);
    painter.drawLine(0,0,50,50);
    painter.restore(); //恢复以前的坐标系状态
    painter.drawLine(0,0,50,50);
    //利用好这两个函数，可以实现快速的坐标系切换，绘制出不同的图形。
#endif
}
