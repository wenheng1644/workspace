#include "netResolver.h"
#include "memory"
#include "algorithm"
#include "../netMsg/netMsg.h"


netResolver* netResolver::m_ptr = nullptr;

std::mutex netResolver::m_mutex;


u_short netMsg::makeChceknum(netHead &head)
{
    u_short checknum = 0;
    checknum = head.len | head.type;
    checknum ^= head.version;

    return checknum;
}

bool netMsg::isVaildChecknum(netHead &head)
{
    u_short value = makeChceknum(head);
    if(value != head.checknum)
        return false;

    return true;
}

u_short netMsg::maketypenum(const netHead& head)
{
    u_short v = head.type | head.subtype << 8;
    return v;
}


tm netTimeResolver::getTimeData(const time_t& t)
{
    std::tm res = *std::localtime(&t);
    return res;
}

std::string netTimeResolver::getTimeString(const time_t& t)
{
    std::tm tm_t = getTimeData(t);
    std::string res(std::asctime(&tm_t));

    std::replace_if(res.begin(), res.end(), [](char c) {
        if(c == '\n' || c == '\t')
            return true;
        return false;
    }, '\0');
    return res;
}

std::string netTimeResolver::getTimeString(const tm& t)
{
    std::string res(std::asctime(&t));

    std::replace_if(res.begin(), res.end(), [](char c) {
        if(c == '\n' || c == '\t')
            return true;
        return false;
    }, '\0');
    return res;
}

netMsg netResolver::makeNetMsg(const std::string& datas, u_char type, u_char subtype, u_char version, dataInfo info)
{
    netHead head;
    head.len = strlen(datas.c_str());
    head.type = type;
    head.subtype = subtype;
    head.version = version;
    head.info = info;
    head.checknum = netMsg::makeChceknum(head);

    netMsg msg;
    msg.head = head;
    msg.body = datas;

    return msg;
}

dataInfo netResolver::makeDataInfo(const std::string &ip, const std::string &name, time_t time) {
    dataInfo info;
    memcpy(info.ip, ip.c_str(), sizeof(info.ip));
    memcpy(info.name, name.c_str(), sizeof(info.name));
    info.times = time;

    return info;
}

std::string netResolver::getSerializationStrByNetMsg(const netMsg &msg) {
    char buff[MAXBYTES] = {0};
    memcpy(buff, (char*)&(msg.head), sizeof(netHead));

    size_t headlen = sizeof(netHead);
    size_t bodylen = msg.head.len;
    std::string msgBuff(headlen + bodylen, 0);

    memcpy((char*)msgBuff.data(), buff, headlen);
    memcpy((char*)msgBuff.data() + headlen, msg.body.c_str(), bodylen);

    return msgBuff;
}


