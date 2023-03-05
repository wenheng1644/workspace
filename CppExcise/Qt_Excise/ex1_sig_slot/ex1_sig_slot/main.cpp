#include <QCoreApplication>
#include "sender.h"
#include "recvier.h"
#include <thread>

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

//    return a.exec();

    Sender s;
    Recvier r;

    QObject::connect(&s, &Sender::value_change, &r, &Recvier::handle_sig);

    s.data_input();
}
