//
// Created by wenheng on 23-7-2.
//

#ifndef BOOST_ASIO_NEW_BASE_CMD_H
#define BOOST_ASIO_NEW_BASE_CMD_H

#include "../common/commonClass.h"
#include "../netMsg/netMsg.h"
#include "../common/user.h"

#include "memory"

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

#include "QtCore/QDataStream"
#include "QtCore/QVector"

#define MAKEVALUE(subid, id)  (((subid) << 8) | (id))
/*
 * 协议主协议号：
 */


/********************************************/





//命令包管理器
//class cmdManager : public Singleton<cmdManager>{
//public:
//
//};


//命令基类
template <u_char cmd_type = 0, u_char cmd_subtype = 0>
struct baseCmd
{
    u_char type = cmd_type;        //主协议号
    u_char subtype = cmd_type;     //子协议号

private:
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & type;
        ar & subtype;
    }

};

typedef baseCmd<> BaseCmd;
QDataStream& operator<<(QDataStream& o, BaseCmd cmd);






#define CMD_PLAYERBASE 1

#define PLAYERCHECK 1

template <u_char subtype = 0>
struct baseplayerCmd : public baseCmd<CMD_PLAYERBASE, subtype>
{
    user userinfo;
    std::vector<user> otherUsers;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & boost::serialization::base_object<baseCmd<CMD_PLAYERBASE, subtype>>(*this);
        ar & userinfo;
    }
};


struct playcheckLoginCmd : public baseplayerCmd<PLAYERCHECK>
{
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & boost::serialization::base_object<baseplayerCmd<PLAYERCHECK>>(*this);
    }
};

QDataStream& operator<<(QDataStream& o, playcheckLoginCmd& cmd);
QDataStream& operator>>(QDataStream& o, playcheckLoginCmd& cmd);

playcheckLoginCmd getData(QDataStream& o);
playcheckLoginCmd getCmdBySerStr(const std::string& str, size_t len);




#endif //BOOST_ASIO_NEW_BASE_CMD_H
