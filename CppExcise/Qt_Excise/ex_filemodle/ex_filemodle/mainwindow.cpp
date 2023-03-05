#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_modle(new QFileSystemModel(this))
{
    ui->setupUi(this);

    m_modle->setRootPath(QDir::rootPath());
    ui->treeView->setModel(m_modle);
    ui->listView->setModel(m_modle);

    QObject::connect(ui->treeView, &QTreeView::clicked, ui->listView,&QListView::setRootIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString path = m_modle->filePath(index);
    qDebug() << "str = " << path;

    QString strSize;

    if(!m_modle->isDir(index))
    {
        qint64 size = m_modle->size(index);


        if(size < 1024)
            strSize = QString::number(size) + "B";
        else if(size < pow(1024, 2))
            strSize = QString::number(size / 1024) + "KB";
        else if(size < pow(1024, 3))
            strSize = QString::number(size / pow(1024,2)) + "MB";
        else
            strSize = QString::number(size / pow(1024,3)) + "G";
    }

    path += " " + strSize;
    ui->statusbar->showMessage(path);

}

