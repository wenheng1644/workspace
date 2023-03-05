#include "widget.h"

#include <QApplication>
#include <QStyle>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(800, 600);

    QFile file("mystyle.css");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "open error";
        return -1;
    }

    QString content = QString::fromLatin1(file.readAll());
    w.setStyleSheet(content);

    w.show();
    return a.exec();
}
