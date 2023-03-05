#ifndef RECVIER_H
#define RECVIER_H

#include <QObject>

class Recvier : public QObject
{
    Q_OBJECT
public:
    explicit Recvier(QObject *parent = nullptr);
    void handle_sig(int value);
signals:

};

#endif // RECVIER_H
