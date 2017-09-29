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

//现在我们来实现在窗口上显示图片，并学习怎样将图片进行平移，缩放，旋转和扭曲。这里
//我们是利用 QPixmap 类来实现图片显示的。
void Dialog::paintEvent(QPaintEvent *)
{
#if 0
    QPainter painter(this);
    QPixmap pix;
    pix.load("E:/temp/QtExercise/painter05_paintimg/images/logo.png");
    painter.drawPixmap(0,0,100,100,pix);

    painter.translate(100,100); //将（ 100， 100）设为坐标原点
    //将（ 100， 100）设置为了新的坐标原点，所以下面在（ 0， 0）点贴图，就相当于在以前的
    //（ 100， 100）点贴图。
    painter.drawPixmap(0,0,100,100,pix);
#elif 0
    //可以使用 QPixmap 类中的 scaled()函数来实现图片的放大和缩小。
    QPainter painter(this);
    QPixmap pix;
    pix.load("E:/temp/QtExercise/painter05_paintimg/images/logo.png");
    painter.drawPixmap(0,0,100,100,pix);
    qreal width = pix.width(); //获得以前图片的宽和高
    qreal height = pix.height();
    pix = pix.scaled(width*2,height*2,Qt::KeepAspectRatio);
    //将图片的宽和高都扩大两倍，并且在给定的矩形内保持宽高的比值
    painter.drawPixmap(200,200,pix);
#elif 0
    //实现图片旋转
    //旋转使用的是 QPainter 类的 rotate()函数，它默认是以原点为中心进行旋转的。我们要改变
    //旋转的中心，可以使用前面讲到的 translate()函数完成。
    QPainter painter(this);
    QPixmap pix;
    pix.load("E:/temp/QtExercise/painter05_paintimg/images/logo.png");
    painter.translate(50,50); //让图片的中心作为旋转的中心
    painter.rotate(90); //顺时针旋转 90 度
    painter.translate(-50,-50); //使原点复原
    painter.drawPixmap(0,0,100,100,pix);
    //这里必须先改变旋转中心，然后再旋转，然后再将原点复原，才能达到想要的效果。
#elif 1
    //实现图片扭曲
    //实现图片的扭曲，是使用的 QPainter 类的 shear(qreal sh， qreal sv)函数完成的。它有两
    //个参数，前面的参数实现横行变形，后面的参数实现纵向变形。当它们的值为 0 时，表示不扭曲。
    QPainter painter(this);
    QPixmap pix;
    pix.load("E:/temp/QtExercise/painter05_paintimg/images/logo.png");
    painter.drawPixmap(0,0,100,100,pix);
    painter.shear(0.5,0); //横向扭曲
//    painter.shear(0,0.5); //纵向扭曲
//    painter.shear(0.5,0.5); //横纵扭曲
    painter.drawPixmap(100,0,100,100,pix);
#endif
}
