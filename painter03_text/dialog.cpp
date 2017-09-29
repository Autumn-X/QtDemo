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
    QPainter painter(this);
    painter.drawText(100,100,"yafeilinux");
#elif 0 //为了更好的控制字体的位置。我们使用另一个构造函数。在帮助里查看 drawText
    QPainter painter(this);
    QRectF ff(100,100,300,200);
    //设置一个矩形
    painter.drawRect(ff);
    //为了更直观地看到字体的位置，我们绘制出这个矩形
    painter.setPen(QColor(Qt::red));
    //设置画笔颜色为红色
    painter.drawText(ff,Qt::AlignHCenter,"yafeilinux");
    //我们这里先让字体水平居中
    //可以看到字符串是在最上面水平居中的。如果想让其在矩形正中间，我们可以使用
    //Qt::AlignCenter。
    //这里我们也可以使用两个枚举变量进行按位与操作，例如可以使用
    //Qt::AlignBottom|Qt::AlignHCenter 实现让文字显示在矩形下面的正中间。
    //对于较长的字符串，我们也可以利用“ \n” 进行换行，例如”yafei\nlinux” 。
#elif 1 //如果要使文字更美观，我们就需要使用 QFont 类来改变字体。
    QFont font("Arial",20,QFont::Bold,true);
    //设置字体的类型，大小，加粗，斜体
    font.setUnderline(true);
    //设置下划线
    font.setOverline(true);
    //设置上划线
    font.setCapitalization(QFont::SmallCaps);
    //设置大小写
    font.setLetterSpacing(QFont::AbsoluteSpacing,5);
    //设置间距
    QPainter painter(this);
    painter.setFont(font);
    //添加字体
    QRectF ff(100,100,300,200);
    painter.drawRect(ff);
    painter.setPen(QColor(Qt::red));
    painter.drawText(ff,Qt::AlignCenter,"yafeilinux");
#endif
}
