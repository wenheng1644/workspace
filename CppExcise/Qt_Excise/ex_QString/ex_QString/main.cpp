#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include "string"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString str1 = "hello world";
    QString str2("what the fuck?");
    QString str3{"hey girls~"};

    std::string stdstring = "std string";
    const char* c_str = "hhhh";
    QString str4 = stdstring.c_str();
    QString str5 = QString::fromLatin1(stdstring.c_str(), stdstring.size());
    QString str6(c_str);

    QString str_com1("what");
    QString str_com2("What");

    if(QString::compare(str_com1, str_com2, Qt::CaseInsensitive) == 0)
        qDebug() << "is compare";
    else
        qDebug() << "is not compare";

    int width = 0;
    width = str1.size() > width ? str1.size() : width;
    width = str2.size() > width ? str2.size() : width;
    width = str3.size() > width ? str3.size() : width;

    qDebug() << str1.rightJustified(width, ' ');
    qDebug() << str2.rightJustified(width, ' ');
    qDebug() << str3.rightJustified(width, ' ');
    QString::setNum()
    return a.exec();
}
