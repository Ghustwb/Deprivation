#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle(QStringLiteral("数据脱敏系统"));
    w.show();
    return a.exec();
}
