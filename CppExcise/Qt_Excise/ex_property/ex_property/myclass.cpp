#include "myclass.h"

Myclass::Myclass(QObject *parent)
    : QObject{parent}, m_age(24), m_name("xwz")
{

}

int Myclass::age()
{
    return m_age;
}

void Myclass::setage(int age)
{
    m_age = age;
    emit sig_agechange(age);
}


