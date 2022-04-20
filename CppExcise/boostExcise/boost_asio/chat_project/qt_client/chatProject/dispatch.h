#ifndef MYDISPATCH_H
#define MYDISPATCH_H

#include "boost/function.hpp"
#include "boost/bind/bind.hpp"
#include "boost/shared_ptr.hpp"

#include "string"
#include "map"

#include "QObject"
#include "QTextEdit"

//class chatRoomWidget;
class myDispatch
{
public:
    static myDispatch* getSington()
    {
        if(!m_dispatch)
            m_dispatch = new myDispatch;
        return m_dispatch;
    }

    void setChatRoom(boost::shared_ptr<QTextEdit> p)
    {
        m_textEdit = p;
    }
    void sendMsg(char* data)
    {
        m_textEdit->append(data);
    }
    ~myDispatch() {}

private:
    static myDispatch* m_dispatch;
    boost::shared_ptr<QTextEdit> m_textEdit;
    myDispatch()  {}

//signals:
//    void signal_sendmsg(std::string msg);

//};

//dispatch* dispatch::m_dispatch = nullptr;

//namespace dispatch {


};

#endif // DISPATCH_H
