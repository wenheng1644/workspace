#include <QCoreApplication>
#include "test_a.h"

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

    test_A A;

    test_A* p1 = new test_A(&A);
    test_A* p2 = new test_A(&A);

    A.dumpObjectTree();
//    return a.exec();
}
