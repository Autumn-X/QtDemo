#ifndef MYITEM_H
#define MYITEM_H
#include <QGraphicsItem>

class MyItem : public QGraphicsItem
{
public:
    MyItem();
    // 因为QGraphicsItem是抽象类，所以必须最少实现下面两个纯虚函数
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // MYITEM_H
