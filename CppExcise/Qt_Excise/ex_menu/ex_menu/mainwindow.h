#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTime>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_statusBar();


private:
    QLabel * m_labelTime;
    QAction * m_viewStautsBar;


    // QObject interface
protected:
    void timerEvent(QTimerEvent *event) override;
};
#endif // MAINWINDOW_H
