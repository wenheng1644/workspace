#include "sender.h"
#include <QDebug>
#include <iostream>
#include <thread>
Sender::Sender(QObject *parent)
    : QObject{parent}
{

}

void Sender::data_input()
{
    qDebug() << "start to loop";
    int value;
    std::cout << "current tid = " << std::this_thread::get_id() << std::endl;
    while(true)
    {
        std::cout << "input value = ";
        scanf("%d", &value);
        emit value_change(value);
    }
}
