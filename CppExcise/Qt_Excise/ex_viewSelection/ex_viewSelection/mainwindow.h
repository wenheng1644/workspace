#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QItemSelectionModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actioncurItem_triggered();

    void on_actiontoggle_triggered();

    void on_updateSelection(const QItemSelection& selected1, const QItemSelection& selected2);
    void on_changeCurrent(const QModelIndex& index, const QModelIndex& preIndex);
private:
    Ui::MainWindow *ui;
    QStandardItemModel * m_model;
    QTableView * m_view;
};
#endif // MAINWINDOW_H
