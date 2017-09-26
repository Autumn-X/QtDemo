/* 利用按钮的 auto repeat 属性，实现按钮长按自动加速 */
#ifndef BTNKEEPPRESS_H
#define BTNKEEPPRESS_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class BtnKeepPress;
}

class BtnKeepPress : public QMainWindow
{
    Q_OBJECT

public:
    explicit BtnKeepPress(QWidget *parent = 0);
    ~BtnKeepPress();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:

    void on_btnDec_clicked();

    void on_btnInc_clicked();

private:
    Ui::BtnKeepPress *ui;

    int m_auto_repeat_count; // 长按计数(即自动重复次数)
    int m_self_inc; // 长按自增长值
    int m_value;
    const int m_inc_max = 20; // 最大增长量

    void SeleIncValuePro();
    void SetValue(int value);
};

#endif // BTNKEEPPRESS_H
