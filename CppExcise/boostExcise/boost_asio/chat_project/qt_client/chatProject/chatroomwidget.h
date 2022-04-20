#ifndef CHATROOMWIDGET_H
#define CHATROOMWIDGET_H

#include <QWidget>
#include <QKeyEvent>

//#include "../../client/client.h"
#include "../../client/client.h"
#include "boost/shared_ptr.hpp"

//class chat_client;

namespace Ui {
class chatRoomWidget;
}

class chatRoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit chatRoomWidget(QWidget *parent = nullptr);
    ~chatRoomWidget();

    void clearContent();
    void setClient(boost::shared_ptr<chat_client>& p)
    {
        m_clientPtr = p;
    }

    void deliverMsg(char* data);

    void showMsg(QString msg);

protected:
    bool eventFilter(QObject *obj, QEvent *e) override;
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::chatRoomWidget *ui;
    boost::shared_ptr<chat_client> m_clientPtr;

    void sendmsg();

public slots:
    void slot_sendmsg(const std::string& msg);

    void slot_disconnect();

private slots:
    void on_pushButton_help_clicked();
};

#endif // CHATROOMWIDGET_H
