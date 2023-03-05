#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QLocale>
#include <QCollator>
#include <QDebug>
#include <QTextStream>
#include <iostream>
#include <QSet>
const int STR_EQUAL = 0;
void test_container1()
{
//    QTextStream stream(stdin);
    while(true)
    {
        QString content;
        std::string str;
        std::getline(std::cin, str);

        content = QString::fromStdString(str);
        qDebug() << "content:" << content;

        if(content.compare('q', Qt::CaseInsensitive) == STR_EQUAL)
            break;

        QList<QString> list = content.split(' ');

        for(auto word : list)
            qDebug() << word;
    }
    qDebug() << "quit";
}

void test_QSet()
{
    QSet<QString> set{"xwz", "khx", "lyy"};
    QSet<QString> set2{"xjj", "xzy", "khx"};

    qDebug() << "set count = " << set.size();
    qDebug() << "set2 count = " << set2.size();

    set.unite(set2);
    qDebug() << "unite set count = " << set.size();

    QList<QString> list(set.begin(), set.end());

    for(auto v : list)
        qDebug() << v;
}

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

//    QList<QString> vals{"徐伟镇", "刘烨仪", "徐紫泳", "邝慧娴"};
//    for(auto name : vals)
//        qDebug() << name;


//    vals << "陈泽琪" << "杨尤";

//    QLocale cn(QLocale::Chinese);
//    QCollator coll(cn);

//    std::sort(vals.begin(), vals.end(), coll);
//    qDebug() << "***********************************";
//    for(QString name : vals)
//        qDebug() << name;

    test_QSet();
    return 0;
}
