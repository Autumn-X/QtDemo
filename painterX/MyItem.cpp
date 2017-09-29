#include "MyItem.h"
#include <QPainter>

MyItem::MyItem()
{

}

QRectF MyItem::boundingRect() const
{ // 返回项的外框，场景类利用这个外框来确定项的位置
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust, 36 + adjust, 60 + adjust);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{ // 绘制项
  painter->drawRect(0,0,20,20);
}
