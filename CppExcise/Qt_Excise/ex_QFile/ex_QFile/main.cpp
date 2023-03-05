#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <string>

void test_fileRW()
{
    qDebug() << "app file path:" << qApp->applicationDirPath();
    std::string str;
    std::cout << "your filename = ";
    std::cin >> str;

    std::cout << "file name = " << str << std::endl;

    char c;
    while((c = fgetchar()) != '\n')
    {
        qDebug() << "buf char = " << QString(c);
    }

    QFile f;
    f.setFileName(QString(str.c_str()));
    if(f.exists())
    {
        qDebug() << "file is exist";
        if(!f.open(QIODevice::ReadOnly))
        {
            qWarning("file open error");
            return;
        }

        QTextStream in(&f);
        int index{};
        while(!in.atEnd())
        {
            QString line = in.readLine();
            qDebug() << QString("line%1").arg(++index) << line;
        }
        qDebug() << "total line count = " << index;
    }
    else
    {
        qDebug() << "file is not exist";
        if(!f.open(QIODevice::WriteOnly))
        {
            qWarning("file open error");
            return;
        }

        std::string line;
        QTextStream out(&f);
        while(std::getline(std::cin, line))
        {
            QString q_str(line.c_str());
            qDebug() << QString(15, '-');
            qDebug() << "q_str = " << q_str;
            std::cout << "line = " << line << std::endl;
            qDebug() << QString(15, '-');
            if(q_str.isEmpty())
            {
                qDebug() << "empty";
                break;
            }

            if(q_str.compare("q\n", Qt::CaseInsensitive) == 0 || q_str.compare("q", Qt::CaseInsensitive) == 0)
            {
                qDebug() << "quit";
                break;
            }

            out << q_str << '\n';

        }
    }
    qDebug() << "program done";
    f.close();
}

void test_copy()
{
    QTextStream in(stdin);
    QString src, dest;
    in >> src >> dest;

    if(src.isEmpty() || dest.isEmpty())
        return;

    QFile src_file(src);
    if(!src_file.exists())
    {
        qWarning() << QString("file = %1 is not exist").arg(src);
        return;
    }

    if(!QFile::copy(src, dest))
    {
        qWarning("copy error");
        return;
    }
    qDebug() << "copy successfully";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    test_copy();
    return 0;
}
