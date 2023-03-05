#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>
#include <QTreeView>
#include <QTableView>
#include <QStandardItemModel>
#include "stringlistmodel.h"

void test_stringlistModel()
{

}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QStandardItemModel model;
//    QStandardItem* parentItem = model.invisibleRootItem();

//    QStandardItem* item = new QStandardItem("A");
//    parentItem->appendRow(item);

//    QStandardItem* item2 = new QStandardItem("B");
//    parentItem->appendRow(item2);


//    QStandardItem* item1_1 = new QStandardItem("A-1");
//    item1_1->setToolTip("tips: A-1");
//    item->appendRow(item1_1);

//    QTreeView view;
//    view.setModel(&model);
//    view.show();

//    qDebug() << model.rowCount();
//    qDebug() << model.rowCount(item->index());


//    test_stringlistModel();
    QStringList list{"徐伟镇", "刘烨仪"};
    StringListModel model(list);

    model.insertRows(model.rowCount(QModelIndex()), 2, QModelIndex());
    QTableView view;
    view.setModel(&model);

    view.setSelectionMode(QAbstractItemView::ExtendedSelection);
    view.setDragEnabled(true);
    view.setAcceptDrops(true);
    view.setDropIndicatorShown(true);

    view.show();

    return a.exec();
}
