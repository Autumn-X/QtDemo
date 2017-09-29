#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::Dialog *ui;

    QPixmap pix;
    QPoint lastPoint;
    QPoint endPoint;

    int scale;
    QPushButton *pushBtn;

    QPixmap tempPix; //临时画布
    bool isDrawing; //标志是否正在绘图

private slots:
    void zoomIn();
};

#endif // DIALOG_H
