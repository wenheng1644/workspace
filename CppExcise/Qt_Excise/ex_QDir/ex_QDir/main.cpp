#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QDebug>

void test_filelist()
{
    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    auto list = dir.entryInfoList();
    for(auto & info : list)
    {
        qDebug() << QString("file name = %1%2size = %3").arg(info.fileName(), 20).arg(QString(5, ' ')).arg(info.size(), 10) << "bytes";
    }
    qDebug() << dir.currentPath();
}

void test_file_dir()
{
    qDebug() << "homepath = " << QDir::homePath();
    qDebug() << "root = " << QDir::rootPath();
    qDebug() << "current = " << QDir::currentPath();
    QDir dir;
    qDebug() << "dir.currentPath() = " << dir.currentPath();
    dir.mkdir("testdir");
    dir.mkpath("test2dir/temp");

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    test_file_dir();
    return 0;
}
