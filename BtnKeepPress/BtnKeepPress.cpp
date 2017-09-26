#include "BtnKeepPress.h"
#include "ui_BtnKeepPress.h"

BtnKeepPress::BtnKeepPress(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BtnKeepPress)
{
    ui->setupUi(this);

    m_auto_repeat_count = 0;
    m_self_inc = 1;
    m_value = 0;
    ui->btnDec->setAutoRepeat(true); // 设置按钮自动重复点击事件
    ui->btnInc->setAutoRepeat(true);
    qApp->installEventFilter(this); // 安装事件过虑器
}

BtnKeepPress::~BtnKeepPress()
{
    qApp->removeEventFilter(this);
    delete ui;
}

bool BtnKeepPress::eventFilter(QObject *watched, QEvent *event)
{
    QList<QPushButton *> btnMove; // 记录要监控的按钮
    btnMove.append(ui->btnDec);
    btnMove.append(ui->btnInc);

    foreach (QPushButton * L, btnMove){
        if ((L->objectName() == watched->objectName())){
            if (event->type() == QEvent::MouseButtonRelease){
                if (!((QKeyEvent *)event)->isAutoRepeat()){ // 按钮松开
                    m_auto_repeat_count = 0;
                    m_self_inc = 1;
                }
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void BtnKeepPress::SeleIncValuePro()
{
    if (m_self_inc < m_inc_max){
        ++ m_auto_repeat_count;
        m_self_inc += m_auto_repeat_count / 10;
    }else{
        m_self_inc = m_inc_max;
    }
}

void BtnKeepPress::SetValue(int value)
{
    m_value += value;
    ui->labelValue->setText(QString::number(m_value));
}

void BtnKeepPress::on_btnDec_clicked()
{
    SeleIncValuePro();
    SetValue(-m_self_inc);
}

void BtnKeepPress::on_btnInc_clicked()
{
    SeleIncValuePro();
    SetValue(m_self_inc);
}
