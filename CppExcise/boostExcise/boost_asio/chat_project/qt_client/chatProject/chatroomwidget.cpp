#include "chatroomwidget.h"
#include "ui_chatroomwidget.h"

#include <QIcon>
#include "QMessageBox"
#include <iostream>

chatRoomWidget::chatRoomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatRoomWidget)
{
    ui->setupUi(this);

    ui->textEdit_msg->setReadOnly(true);

    ui->textEdit_content->installEventFilter(this);

//    connect(m_clientPtr.get(), &chat_client::signal_disconnect, this, &chatRoomWidget::slot_disconnect);
    QIcon help_icon(":/images/help.png");
    ui->pushButton_help->setIcon(help_icon);
    ui->pushButton_help->setIconSize(QSize(35,35));
    ui->pushButton_help->setStyleSheet("background-color:transparent");
    ui->pushButton_help->setText("帮助");
    ui->pushButton_help->setFocusPolicy(Qt::NoFocus);

}

chatRoomWidget::~chatRoomWidget()
{
    delete ui;
}

void chatRoomWidget::clearContent()
{
    ui->textEdit_content->clear();
    ui->textEdit_msg->clear();
}

void chatRoomWidget::deliverMsg(char *data)
{
    ui->textEdit_msg->append(data);
}

void chatRoomWidget::showMsg(QString msg)
{
    ui->textEdit_msg->append(msg);
}

bool chatRoomWidget::eventFilter(QObject *obj, QEvent *e)
{
    Q_ASSERT(obj == ui->textEdit_content);
//    std::cout << "come here" << std::endl;
    if (e->type() == QEvent::KeyPress)
        {
            QKeyEvent *event = static_cast<QKeyEvent*>(e);
            if ((event->key() == Qt::Key_Return) /*&& (event->modifiers() & Qt::ControlModifier)*/)
            {
                std::cout << "hello" << std::endl;

                sendmsg();
                return true;
            }
        }
    return false;
}

void chatRoomWidget::closeEvent(QCloseEvent *event)
{
//    std::cout << "cout: " << m_clientPtr.use_count() << std::endl;
    m_clientPtr->close();
//    std::cout << "cout: " << m_clientPtr.use_count() << std::endl;
}

void chatRoomWidget::sendmsg()
{
    auto msg = ui->textEdit_content->toPlainText().toStdString();

    if(strlen(msg.c_str()) + USERNAME_LEN > BODY_LEN)
    {
        QMessageBox::warning(this, "警告", "输入数据太多了!!!");
        return;
    }

    std::string username = m_clientPtr->UserName();

    chatMsg sendMsg;
    char userData[BODY_LEN] = {};

    strcat(userData, username.c_str());
    size_t userName_Len = strlen(username.c_str());
    memcpy(userData, username.c_str(), userName_Len);
    memset(userData + userName_Len, ' ', USERNAME_LEN - userName_Len);
    memcpy(userData + USERNAME_LEN, msg.c_str(), strlen(msg.c_str()));

    sendMsg.bodyLen(strlen(msg.c_str()) + USERNAME_LEN);
    sendMsg.encode();

    memcpy(sendMsg.body(), userData, strlen(userData));

//    ui->textEdit_msg->append(msg);
//    std::cout << "cout: " << m_clientPtr.use_count() << std::endl;
    m_clientPtr->write(sendMsg);
    ui->textEdit_content->clear();
}

void chatRoomWidget::slot_sendmsg(const std::string &msg)
{
    ui->textEdit_msg->append(QString(msg.data()));
}

void chatRoomWidget::slot_disconnect()
{
    QMessageBox::warning(this, "提示", "与服务器断开连接...");
    m_clientPtr->close();
    close();
}

//void chatRoomWidget::appendMsg(const std::string &msg)
//{
//    ui->textEdit_msg->append(QString(msg.data()));
//}



void chatRoomWidget::on_pushButton_help_clicked()
{
    QMessageBox::information(this, "帮助", "按下回车键即可发送消息");
}
