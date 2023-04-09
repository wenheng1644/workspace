#ifndef NETWORKRESOLVER_HEAD
#define NETWORKRESOLVER_HEAD

#define NETBODYLEN 1024

#include "iostream"
#include "cstring"
#include "mutex"
#include "vector"
#include "memory"
#pragma (1)
struct netHead
{
    u_short     len;        //包长度
    u_char      type;       //消息类型
    u_short     version;    //版本号
    u_short     checknum;   //校验码 len | type ^ version

    netHead() { std::memset(this, 0, sizeof(netHead));}
};

struct netMsg
{
    netHead head;   //数据头
//    std::shared_ptr<char> body;     //数据体
    char body[NETBODYLEN];
    netMsg() {
        memset(&head, 0, sizeof(head));
        memset(body, 0, sizeof(body));
    }

    static u_short makeChceknum(netHead& head);
    static bool isVaildChecknum(netHead& head);
};

class netResolver
{
public:
    static netResolver* generator()
    {
        std::lock_guard<std::mutex> l(m_mutex);     //防止多线程同时访问
        if(!m_ptr)
        {
            m_ptr = new netResolver();
        }
        return m_ptr;
    }

    std::shared_ptr<char> compose(netHead& head, char* body, size_t bodylen);
    std::shared_ptr<char> compose(netMsg& msg);
    void compose(netHead& head, char* body, size_t bodylen, char* data);
     std::shared_ptr<netMsg> resolver(const char* data, size_t len);



private:
    netResolver() = default;
    static netResolver* m_ptr;
    static std::mutex m_mutex;
};

#endif