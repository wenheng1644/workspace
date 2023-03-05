#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QTableView>
#include <QAction>
#include <QSplitter>
#include <QStandardItemModel>


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
    void on_actionOpen_triggered();

private:
    void createMenu();
    void setupModel();
    void setupView();
private:
    Ui::MainWindow *ui;
    QStandardItemModel * m_model;
    QTableView * m_tableView;
    QSplitter * m_splitter;
    QMenu * m_menu;
};
#endif // MAINWINDOW_H
