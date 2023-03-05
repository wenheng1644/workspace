#include "recvier.h"
#include <QDebug>
#include <thread>
#include <iostream>

Recvier::Recvier(QObject *parent)
    : QObject{parent}
{

}

void Recvier::handle_sig(int value)
{
    std::cout << "tid:" << std::this_thread::get_id() << "\trecvie data =" << value << std::endl;
}
