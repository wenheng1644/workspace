#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

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
    void on_pushButton_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_clear_clicked();

private:
    QStringListModel * m_model;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
