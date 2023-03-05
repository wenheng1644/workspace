#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QString>
#include <QThread>
class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);
    void data_input();
signals:
    void value_change(int value);

};

#endif // SENDER_H
