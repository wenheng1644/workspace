#include <QCoreApplication>
#include "myclass.h"
#include <QVariant>
#include <QDebug>
#include <QMetaClassInfo>

void test_handle(int v)
{
    qDebug() << "get value =" << v;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Myclass m;
    QObject::connect(&m, &Myclass::sig_agechange, qApp, &test_handle);
    qDebug() <<  m.property("age").toInt();
    qDebug() << m.metaObject()->classInfo(0).value();
    qDebug() << m.property("name").toString();
    m.setProperty("addr", "guangzhou");

    qDebug() << m.property("addr");
    m.setProperty("age", 11);
    return a.exec();
}
