#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    bool ok;
    int v = QInputDialog::getInt(this, "getint", "int", 0, 0, 100, 1, &ok);

    if(ok)
        qDebug() << v;
}


void MainWindow::on_pushButton_2_clicked()
{
    bool ok;
    double v = QInputDialog::getDouble(this, "getdouble", "doouble", 0, 0.0,100.0,1, &ok, Qt::WindowFlags(), 0.1);

    if(ok)
        qDebug() << v;
}


void MainWindow::on_pushButton_3_clicked()
{
    QStringList items{"春", "夏", "秋", "冬"};
    QInputDialog::getItem(this, "getitem", "item", items, 0);
}


void MainWindow::on_pushButton_4_clicked()
{
    QInputDialog::getText(this, "getText", "text");
}

