#ifndef NETWORKRESOLVER_HEAD
#define NETWORKRESOLVER_HEAD

#include "iostream"
#include "cstring"
#include "string"
#include "sstream"

#include "../netMsg/netMsg.h"
#include "mutex"

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

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

    static dataInfo makeDataInfo(const std::string& ip = "", const std::string& name = "", time_t time = 0);
    static netMsg makeNetMsg(const std::string& datas, u_char type, u_char subtype, u_char version = 1, dataInfo info = dataInfo());

    template<typename T>
    static std::string getSerializationStr(const T& v);

    template<typename T>
    static T getReSerializationObjByStr(const std::string& str);

    static std::string getSerializationStrByNetMsg(const netMsg& msg);
private:
    netResolver() = default;
    static netResolver* m_ptr;
    static std::mutex m_mutex;
};



template<typename T>
T netResolver::getReSerializationObjByStr(const std::string &str) {
    T datas;
    std::istringstream ss(str);
    boost::archive::text_iarchive ia(ss);

    ia >> datas;

    return datas;
}

template<typename T>
std::string netResolver::getSerializationStr(const T &v)
{
    std::ostringstream ss;
    boost::archive::text_oarchive oa(ss);

    oa << v;

    return ss.str();
}

namespace netTimeResolver{
    tm getTimeData(const time_t& t);
    std::string getTimeString(const time_t& t);
    std::string getTimeString(const tm& t);
};

#endif
