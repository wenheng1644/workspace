#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QStandardItemModel>
#include <QDataWidgetMapper>

#include "mydelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();
private slots:
    void on_pushButton_pre_clicked();

    void on_pushButton_next_clicked();

    void on_tableView_clicked(const QModelIndex &index);


private:
    void handle_updatebutton();
private:
    QStandardItemModel * m_model;
    QDataWidgetMapper * m_mapper;
    MyDelegate temp;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
