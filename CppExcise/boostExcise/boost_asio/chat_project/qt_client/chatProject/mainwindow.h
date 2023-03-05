#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "boost/shared_ptr.hpp"

#include "chatroomwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(io_service& ioserver, ip::tcp::resolver::iterator iter, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_help_clicked();

    void slot_sendMsg(QString msg);

    void slot_connect(bool connected);

private:
    Ui::MainWindow *ui;
    boost::shared_ptr<chatRoomWidget> m_roomPtr;
    boost::shared_ptr<chat_client> m_clientPtr;

    io_service& m_ioserver;
    ip::tcp::resolver::iterator m_iter;
//    chat_client m_client;
};
#endif // MAINWINDOW_H
