#ifndef NETWORKRESOLVER_HEAD
#define NETWORKRESOLVER_HEAD

#include "../netMsg/netMsg.h"
#include "mutex"

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
    netHead getNetHead(const char* headData);

private:
    netResolver() = default;
    static netResolver* m_ptr;
    static std::mutex m_mutex;
};

namespace netTimeResolver{
    tm getTimeData(const time_t& t);
    std::string getTimeString(const time_t& t);
    std::string getTimeString(const tm& t);
};

#endif