#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_model(new QStandardItemModel(this)), m_mapper(new QDataWidgetMapper(this))
{
    ui->setupUi(this);

    init();

    ui->tableView->setModel(m_model);
//    ui->tableView->setSelectionMode(QAbstractItemView::SelectionMode::);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    QStringList names, addrs, labels;
    QList<int> ages;

    names << "徐伟镇" << "邝慧娴" << "刘烨仪";
    addrs << "广州" << "广州" << "江门";
    ages << 23 << 23 << 24;

    for(int i = 0;i < 3; i++)
    {
        QStandardItem * item = new QStandardItem(names[i]);
        m_model->setItem(i, 0, item);

        item = new QStandardItem(addrs[i]);
        m_model->setItem(i, 1, item);

        item = new QStandardItem(QString::number(ages[i]));
        m_model->setItem(i, 2, item);
    }

    labels << "姓名" << "地址" << "年龄";
    m_model->setHorizontalHeaderLabels(labels);

    m_mapper->setModel(m_model);
    m_mapper->addMapping(ui->lineEdit_name, 0);
    m_mapper->addMapping(ui->lineEdit_addr, 1);
    m_mapper->addMapping(ui->spinBox, 2);

    m_mapper->toFirst();
    ui->pushButton_pre->setEnabled(false);

    MyDelegate * dele = new MyDelegate(this);

    ui->tableView->setItemDelegateForColumn(2, &temp);
}


void MainWindow::on_pushButton_pre_clicked()
{
    m_mapper->toPrevious();
    handle_updatebutton();
}


void MainWindow::on_pushButton_next_clicked()
{
    m_mapper->toNext();
    handle_updatebutton();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->tableView->selectRow(index.row());
    m_mapper->setCurrentModelIndex(index);
}

void MainWindow::handle_updatebutton()
{
    int index = m_mapper->currentIndex();
    if(0 == index)
    {
        ui->pushButton_pre->setEnabled(false);
        ui->pushButton_next->setEnabled(true);
    }
    else if(m_model->rowCount() - 1 == index)
    {
        ui->pushButton_pre->setEnabled(true);
        ui->pushButton_next->setEnabled(false);
    }
    else
    {
        ui->pushButton_pre->setEnabled(true);
        ui->pushButton_next->setEnabled(true);
    }
}

