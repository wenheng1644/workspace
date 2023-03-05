#ifndef TEST_A_H
#define TEST_A_H

#include <QObject>
#include <QDebug>

class test_A : public QObject
{
    Q_OBJECT
public:
    explicit test_A(QObject *parent = nullptr);
    ~test_A();

signals:

};

#endif // TEST_A_H
