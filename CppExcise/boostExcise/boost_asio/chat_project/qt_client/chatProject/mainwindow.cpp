#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dispatch.h"

#include <QIcon>
#include <QMessageBox>

#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
using namespace boost::asio;

MainWindow::MainWindow(io_service& ioserver, ip::tcp::resolver::iterator iter, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_ioserver(ioserver), m_iter(iter), m_clientPtr(new chat_client(ioserver, iter)), m_roomPtr(new chatRoomWidget)
{
    ui->setupUi(this);
    ui->label_title->setText("多人聊天室");
    ui->label_username->setText("用户名");

    ui->pushButton_connect->setText("连接");

    this->setWindowTitle("内测聊天室 ver0.1.0");

    QIcon help_icon(":/images/help.png");
    ui->pushButton_help->setIcon(help_icon);
    ui->pushButton_help->setIconSize(QSize(35,35));
    ui->pushButton_help->setStyleSheet("background-color:transparent");
    ui->pushButton_help->setFocusPolicy(Qt::NoFocus);

    ui->lineEdit_username->setPlaceholderText("随便填个名字");
    std::cout << "mainwindow thread id: " << std::this_thread::get_id() << std::endl;

    QObject::connect(m_clientPtr.get(), &chat_client::signal_sendMsg, this, &MainWindow::slot_sendMsg);

    QObject::connect(m_clientPtr.get(), &chat_client::signal_disconnect, m_roomPtr.get(), &chatRoomWidget::slot_disconnect);

    QObject::connect(ui->lineEdit_username, &QLineEdit::returnPressed, this, &MainWindow::on_pushButton_connect_clicked);

    QObject::connect(m_clientPtr.get(), &chat_client::signal_connect, this, &MainWindow::slot_connect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    std::cout << "mainwindow closed" << std::endl;
    exit(0);
}


void MainWindow::on_pushButton_connect_clicked()
{

    auto content = ui->lineEdit_username->text();
    std::cout << "content.toStdString().size(): " << content.toStdString().size() << std::endl;
    std::cout << "content.isSimpleText(): " << content.isSimpleText() << std::endl;
    content = content.trimmed();
    if(content.isEmpty() || content.isNull())
    {
        QMessageBox::warning(this, "提示", "请正确输入用户名");
        return;
    }

    if(content.toStdString().size() > USERNAME_LEN)
    {
        QMessageBox::warning(this, "提示", "用户名过长");
        return;
    }
    std::string name_str = content.toStdString();
    m_clientPtr->UserName(name_str);
    m_roomPtr->setClient(m_clientPtr);

    m_clientPtr->connect();

//    if(!m_clientPtr->connect())
//    {
//        QMessageBox::warning(this, "提示", "服务器连接失败");
//        return;
//    }
//    std::cout << "on_connect thread id: " << std::this_thread::get_id() << std::endl;

//    m_roomPtr->clearContent();
//    m_roomPtr->resize(1500, 900);
//    m_roomPtr->setWindowTitle("聊天室");
//    m_roomPtr->show();
}

void MainWindow::on_pushButton_help_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("帮助");
    msgBox.setText("多人聊天室首次内测~~~\n点击\"连接\"连接聊天室服务器");
    msgBox.exec();
}

void MainWindow::slot_sendMsg(QString msg)
{
    m_roomPtr->showMsg(msg);
}

void MainWindow::slot_connect(bool connected)
{
    if(!connected)
    {
        QMessageBox::warning(this, "提示", "服务器连接失败");
        return;
    }

    std::cout << "on_connect thread id: " << std::this_thread::get_id() << std::endl;

    m_roomPtr->clearContent();
    m_roomPtr->resize(1500, 900);
    m_roomPtr->setWindowTitle("聊天室");
    m_roomPtr->show();
}
