#include "test_a.h"

test_A::test_A(QObject *parent)
    : QObject{parent}
{
    qDebug() << this << "构建";
}

test_A::~test_A()
{
    qDebug() << this << "析构";
}
