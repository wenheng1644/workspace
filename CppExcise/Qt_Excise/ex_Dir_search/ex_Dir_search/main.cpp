#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QLocale>
#include <QDebug>

void forearchDir(QDir dir, int& cnt, quint64 & bytes)
{
    dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Size | QDir::Reversed);
    auto list = dir.entryInfoList();

    QString space(10, ' ');
//    int filenamewidth = 80;

//    for(auto & info : list)
//    {
//        if(!info.isFile()) continue;
//        QString filename = info.completeBaseName();
//        filenamewidth = filename.size() > filenamewidth ? filename.size() : filenamewidth;
////        qDebug() << QString(15, '*');
////        qDebug() << QString("filename = %1%2leghth = %3").arg(filename).arg(space).arg(filenamewidth);
////        qDebug() << QString(15, '*');
//    }

    for(auto & info : list)
    {
        if(info.isDir())
        {
            QDir curDir;
            curDir.setPath(dir.path() + "\\" + info.fileName());
            forearchDir(curDir, cnt, bytes);
            continue;
        }
        qDebug() << QString("file name = %1%2size = %3bytes%4type = %5").arg(info.fileName(), 0).arg(space) \
                    .arg(info.size(), 7).arg(space)\
                    .arg(info.isFile() ? "file" : "dir", 5);
        cnt++;
        bytes += info.size();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QLocale cn("zh_CN");

    QDir dir;
    dir.setPath("E:\\迅雷下载");
    int cnt = 0;
    quint64 bytes = 0;
    forearchDir(dir, cnt, bytes);

    int bytes_G = bytes / 1024 / 1024 / 1024;

    qDebug() << "file cnt = " << cnt << " bytes = " << bytes << " bytes_M = " << bytes_G;
    return 0;
}
