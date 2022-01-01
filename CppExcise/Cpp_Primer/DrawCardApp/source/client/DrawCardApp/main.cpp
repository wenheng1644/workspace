#include "mainwindow.h"
#include <QDir>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1500,1200);
    w.show();
    w.setWindowTitle("抽卡模拟器");
    return a.exec();
}
