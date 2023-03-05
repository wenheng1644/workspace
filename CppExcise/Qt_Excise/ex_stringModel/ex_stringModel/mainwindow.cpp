#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_model(new QStringListModel(this))
{
    ui->setupUi(this);
    QStringList list{"徐伟镇", "邝慧娴", "刘烨仪"};
    m_model->setStringList(list);
    ui->listView->setModel(m_model);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    m_model->insertRow(m_model->rowCount());
    QModelIndex index = m_model->index(m_model->rowCount() - 1);
    m_model->setData(index, "新老婆");
    ui->listView->edit(index);
}


void MainWindow::on_pushButton_reset_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    ui->listView->edit(index);
}


void MainWindow::on_pushButton_del_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    m_model->removeRow(index.row());
}


void MainWindow::on_pushButton_clear_clicked()
{
    m_model->removeRows(0, m_model->rowCount());
}

