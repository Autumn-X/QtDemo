#include "BtnKeepPress.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BtnKeepPress w;
    w.show();

    return a.exec();
}
