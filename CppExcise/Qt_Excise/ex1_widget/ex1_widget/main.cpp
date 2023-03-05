#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qDebug() << "当前路径:" << qApp->applicationFilePath();
    qDebug() << "当前应用程序类名" << qApp->metaObject()->className();
    qDebug() << "当前程序名:" << qApp->applicationName();
    qApp->setApplicationName("test");
    qApp->setApplicationDisplayName("test");
    return a.exec();
}
