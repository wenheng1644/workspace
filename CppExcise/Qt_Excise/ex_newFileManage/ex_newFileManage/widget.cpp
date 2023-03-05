#include "widget.h"
#include "./ui_widget.h"
#include <QFileInfo>

#include <thread>


QString Widget::transFromBytes(quint64 bytes)
{
    QString res;

    if(bytes < Kbytes)
    {
        res = QString::number(bytes) + "B";
    }
    else if(bytes < Mbytes)
    {
        res = QString::number(bytes / Kbytes) + "KB";
    }
    else if(bytes < Gbytes)
    {
        res = QString::number(bytes / Mbytes) + "MB";
    }
    else
    {
        res = QString::number(bytes / Gbytes) + "GB";
    }

    return res;
}

quint64 Widget::transFromFormatBytes(quint64 value, int index)
{
    quint64 base = pow(Kbytes, index);
    return base * value;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget), m_model(new QFileSystemModel(this)), m_filter(new FileSizeFilter(this)), m_dialg(new FileBytesDialog(this))
{
    ui->setupUi(this);

    init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    ui->lineEdit->setReadOnly(true);

    ui->comboBox->addItems(QStringList{"搜索", "搜索并清除"});

    ui->treeView->setModel(m_filter);


    QModelIndex index = m_model->setRootPath(QDir::rootPath());
    qDebug() << "rootpath =" << m_model->rootPath();
    m_filter->setSourceModel(m_model);
    ui->treeView->setSortingEnabled(true);
//    ui->treeView->

}

void Widget::search(QDir& dir, const quint64& minBytes, FileInfoListType& res)
{
//    dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
//    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Files);

    for(const auto& info : list)
    {
        if(info.isDir())
        {
            QDir curDir(info.absoluteFilePath());
            search(curDir, minBytes, res);
        }
        else if(info.isFile() && info.size() >= minBytes)
        {
            res.append({info.fileName(), info.size()});
        }
    }

}

void Widget::test()
{
    qDebug() << "rootpath =" << m_model->rootPath();
    QModelIndex index_source = m_model->index(ui->lineEdit->text());

    qDebug() << "source index = " << index_source.data().toString();
    qDebug() << "map index = " << m_filter->mapFromSource(index_source).data().toString();
}

void Widget::_thread(QDir dir, quint64 bytes, QString path)
{
    FileInfoListType list;

    search(dir, bytes, list);

    if(list.empty())
    {
        qDebug() << "搜索为空";
        return;
    }

    m_filter->setMinBytes(bytes);


    for(const auto& info : list)
    {
        qDebug() << "文件名 = " << info.first << " 大小 = " << info.second;
        ui->textEdit->append(QString("name = %1").arg(info.first) + " 大小 = " + transFromBytes(info.second));
    }
    qDebug() << "path = " << path;



    QModelIndex indexSource = m_model->index(path);
    QModelIndex indexMap = m_filter->mapFromSource(indexSource);
    ui->treeView->setRootIndex(indexMap);

    ui->textEdit->append("搜索结束...");

}


void Widget::on_pushButton_rootPath_clicked()
{
    QString path(ui->lineEdit->text());
    QFileInfo info(path);
    QString dir = QFileDialog::getExistingDirectory(this, "", path.isEmpty() || !info.exists() ? QDir::rootPath() : path);
    if(dir.isEmpty()) return;

    ui->lineEdit->setText(dir);
}


void Widget::on_pushButton_ok_clicked()
{
//    test();
    QString path(ui->lineEdit->text());
    if(path.isEmpty()) return;

    QFileInfo info(path);
    if(!info.exists()) return;


    QDir dir(path);
    if(!dir.exists()) return;

    int ans;
    if((ans = m_dialg->exec()) != QDialog::Accepted)
    {
        qDebug() << "ans = " << ans;
        return;
    }
    ui->textEdit->clear();

    quint64 value = m_dialg->value();
    int curComboxIndex = m_dialg->index();
    quint64 totalBytes = transFromFormatBytes(value, curComboxIndex);
    qDebug() << "value = " << value << " curComboxIndex = " << curComboxIndex << " totalBytes = " << totalBytes;

    std::thread t1(std::bind(&Widget::_thread, this, dir, totalBytes, path));
    t1.join();
}

