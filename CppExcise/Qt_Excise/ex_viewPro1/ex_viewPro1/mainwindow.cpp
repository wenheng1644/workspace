#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_model(new QStandardItemModel(4,4,this)), m_tableView(new QTableView(this)), m_splitter(new QSplitter(this))
{
    ui->setupUi(this);
    createMenu();
    setupModel();
    setupView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenu()
{
    m_menu = ui->menubar->addMenu("file");
    m_menu->addAction(ui->actionOpen);
}

void MainWindow::setupModel()
{
    m_model->setHeaderData(0, Qt::Horizontal, "部门");
    m_model->setHeaderData(1, Qt::Horizontal, "女");
    m_model->setHeaderData(2, Qt::Horizontal, "男");
    m_model->setHeaderData(3, Qt::Horizontal, "退休");
}

void MainWindow::setupView()
{
    m_tableView->setModel(m_model);
    QItemSelectionModel * selectonModel = m_tableView->selectionModel();

    QObject::connect(selectonModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), m_tableView, SLOT(selectionChanged(QItemSelection,QItemSelection)));
    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_tableView);
    setCentralWidget(m_splitter);
}



void MainWindow::on_actionOpen_triggered()
{
    QString name = QFileDialog::getOpenFileName(this, " 打 开 ", QDir::currentPath(), "(*.txt)");
    if(name.isEmpty())
        return;

    QFile file(name);

    if(!file.exists())
        return;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    m_model->removeRows(0, m_model->rowCount());
    int row = 0;
    QTextStream stream(&file);
    QString line;

    while(!stream.atEnd())
    {
        line = stream.readLine();
        if(!line.isEmpty())
        {
            m_model->insertRows(row, 1);
            QStringList list = line.split("," , Qt::KeepEmptyParts);

            m_model->setData(m_model->index(row, 0), list[0]);
            m_model->setData(m_model->index(row, 1), list[1]);
            m_model->setData(m_model->index(row, 2), list[2]);
            m_model->setData(m_model->index(row, 3), list[3]);

            row++;
        }
    }
    file.close();
}

