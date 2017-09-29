#include "MyItem.h"
#include <QApplication>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    // 新建场景
    scene.setSceneRect(-300, -300, 600, 600);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    // 设置项索引方式

    MyItem *item=new MyItem;
    scene.addItem(item);
    // 新建项并添加到场景中

    QGraphicsView view(&scene);
    // 为场景新建视图
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.resize(400,300);
    view.show();
    // 设置视图的几个属性，并显示出来

    return a.exec();
}
