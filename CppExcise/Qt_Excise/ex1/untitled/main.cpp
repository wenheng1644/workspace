#include <QCoreApplication>
#include <QtGui/QGuiApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "Qt Version = " << qVersion() << std::endl;
//    system("pause");
    qDebug() << "Qt version:" << qVersion();
    qDebug() << a.metaObject()->className();
    qDebug() << a.applicationFilePath();

//    a.dumpObjectTree();
//    a.dumpObjectInfo();

    qGuiApp->dumpObjectInfo();
    qGuiApp->dumpObjectTree();
    return a.exec();
}
