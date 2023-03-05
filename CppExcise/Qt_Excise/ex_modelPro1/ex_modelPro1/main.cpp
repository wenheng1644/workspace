#include "mainwindow.h"

#include <QApplication>
#include <QFileSystemModel>
#include <QListView>
#include <QTreeView>
#include <QTableView>
#include <QSplitter>

#include <infotablemodel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFileSystemModel model;
    model.setRootPath(QDir::rootPath());

    InfoTableModel myTableModel;

//    QTreeView tree;
//    QListView list;
    QTableView table;

//    tree.setModel(&model);
//    list.setModel(&model);
    table.setModel(&myTableModel);

//    QObject::connect(&tree, &QTreeView::doubleClicked, &list, &QListView::setRootIndex);
//    QObject::connect(&tree, &QTreeView::doubleClicked, &table, &QTableView::setRootIndex);

//    QSplitter splitter;
//    splitter.addWidget(&tree);
//    splitter.addWidget(&list);
//    splitter.addWidget(&table);

//    splitter.show();
//    MainWindow w;
//    w.show();
    QObject::connect(&table, &QTableView::)
    table.show();
    return a.exec();
}
