#include <QCoreApplication>
#include <QTime>
#include <QDate>
#include <QDebug>
#include <QLocale>
#include <QDateTime>

#include <ctime>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QLocale cn("zh_CN");
    QTime t = QTime::currentTime().currentTime();
    qDebug() << t.toString("hh:mm:ss A");

    QDate dt = QDate::currentDate();
    qDebug() << dt.toString("yyyy MM dd");

    qDebug() << dt.dayOfWeek();
    qDebug() << cn.dayName(dt.dayOfWeek(), QLocale::ShortFormat);

    qDebug() << dt.daysTo(QDate(2023,1,21));

    QDateTime times;
    times.setSecsSinceEpoch(time(0));
    qDebug() << times.toString("yyyy-MM-dd hh:mm:ss A");
    return 0;
}
