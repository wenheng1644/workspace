//
// Created by wenheng on 23-7-2.
//

#ifndef BOOST_ASIO_NEW_USER_H
#define BOOST_ASIO_NEW_USER_H

#include "iostream"
#include "boost/format.hpp"

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

#include "QtCore/QDataStream"
#include "QtCore/QString"

struct user {
    friend QDataStream& operator<<(QDataStream& o, user info);
    friend QDataStream& operator>>(QDataStream& o, user& info);
public:
    user() = default;
    explicit user(const std::string& name, u_char sex = 0, time_t t = time(nullptr));
    user(const user& r);

    user& operator=(const user& r);

    inline std::string name() { return m_name; }
    inline void setname(const std::string& name) { m_name = name; }

    inline u_char sex() { return m_sex; }
    inline time_t loginTime() { return m_login_time; }

private:
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & m_name;
        ar & m_sex;
        ar & m_login_time;
    }


private:
    std::string m_name;
    u_char m_sex;           //0是女性&1是男性
    time_t m_login_time;
};
QDataStream& operator<<(QDataStream& o, user info);
QDataStream& operator>>(QDataStream& o, user& info);



#endif //BOOST_ASIO_NEW_USER_H
