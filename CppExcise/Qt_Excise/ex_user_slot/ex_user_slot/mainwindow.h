#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QTime>
#include <QTimerEvent>
#include <QStatusBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    void handle_check(int state);
    void handle_push();
private:
    QWidget* m_widget;
    QPushButton* m_push;
    QCheckBox* m_cbox;
    QLabel* m_lable;

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event) override;
};
#endif // MAINWINDOW_H
