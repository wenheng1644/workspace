#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QString>

class Myclass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int age READ age WRITE setage NOTIFY sig_agechange)
    Q_PROPERTY(QString name MEMBER m_name)
    Q_CLASSINFO("version", "1.0.0")
public:
    explicit Myclass(QObject *parent = nullptr);

    int age();
    void setage(int age);
private:
    int m_age;
    QString m_name;
signals:
    void sig_agechange(int age);
};

#endif // MYCLASS_H
