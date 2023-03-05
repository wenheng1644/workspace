#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_model(new QStandardItemModel(7, 4, this)), m_view(new QTableView(this))
{
    ui->setupUi(this);

    for(int row = 0; row < 7; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            QStandardItem * item = new QStandardItem(QString(" %1 ").arg(row * 4 + col));
            m_model->setItem(row, col, item);
        }
    }

    m_view->setModel(m_model);
    setCentralWidget(m_view);

    QItemSelectionModel * selectionModel = m_view->selectionModel();
    QModelIndex index1,index2;
    index1 = m_model->index(1,1);
    index2 = m_model->index(5,2);

    QItemSelection selection(index1, index2);
    selectionModel->select(selection, QItemSelectionModel::Select);

    QModelIndex test = selectionModel->currentIndex();
//    selectionModel->sel
    qDebug() << "row = " << test.row() << " col = " << test.column();

    auto menu = ui->menubar->addMenu("menu");
    menu->addAction(ui->actioncurItem);
    menu->addAction(ui->actiontoggle);

    QTableView* view2 = new QTableView(this);
    view2->setSelectionModel(selectionModel);
    view2->setWindowTitle("view2");
    view2->resize(400,300);
    view2->setModel(m_model);
    view2->show();

    QObject::connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::on_updateSelection);
    QObject::connect(selectionModel, &QItemSelectionModel::currentChanged, this, &MainWindow::on_changeCurrent);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actioncurItem_triggered()
{
    qDebug() << "content = " << m_view->selectionModel()->currentIndex().data().toString();
}


void MainWindow::on_actiontoggle_triggered()
{
    QModelIndex index1, index2;
    index1 = m_model->index(0,0);
    index2 = m_model->index(m_model->rowCount() - 1, m_model->columnCount() - 1);

    m_view->selectionModel()->select(QItemSelection(index1,index2), QItemSelectionModel::Toggle);

}

void MainWindow::on_updateSelection(const QItemSelection &selected1, const QItemSelection &selected2)
{
    qDebug() << "update";
    QModelIndexList list = selected1.indexes();
    for(auto index : list)
    {
        QString text = QString(" %1, %2").arg(index.row()).arg(index.column());
        m_view->model()->setData(index, text);
    }

    list = selected2.indexes();

    for(auto index : list)
    {
        QString text("");
        m_view->model()->setData(index, text);
    }
}

void MainWindow::on_changeCurrent(const QModelIndex &index, const QModelIndex &preIndex)
{
    qDebug() << QString("move(%1, %2) to (%3, %4)").arg(preIndex.row()).arg(preIndex.column())\
                .arg(index.row()).arg(index.column());
}

