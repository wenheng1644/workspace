#include "netResolver.h"
#include "memory"
#include "algorithm"

netResolver* netResolver::m_ptr = nullptr;
std::mutex netResolver::m_mutex;

std::shared_ptr<char> netResolver::compose(netHead &head, char *body, size_t bodylen)
{
    std::shared_ptr<char> data(new char(sizeof(head) + bodylen + 1));
    char *p = data.get();
    char* h =  reinterpret_cast<char*>(&head);
    std::memcpy(p, h, sizeof(head));
    std::memcpy((p + sizeof(head)), body, bodylen);

    return data;
}

std::shared_ptr<netMsg> netResolver::resolver(const char *data,  size_t len)
{
    auto netMsg_ptr = std::shared_ptr<netMsg>(new netMsg);
    memcpy(&(netMsg_ptr->head), data, sizeof(netHead));
    memcpy(netMsg_ptr->body, data + sizeof(netHead), len - sizeof(netHead));

    return netMsg_ptr;
}

std::shared_ptr<char> netResolver::compose(netMsg &msg)
{
    u_short bodyLen = msg.head.len;
    std::shared_ptr<char> data(new char(sizeof(netHead) + bodyLen) + 1);
    std::memcpy(data.get(), &(msg.head), sizeof(netHead));
    std::memcpy(data.get() + sizeof(netHead), msg.body, bodyLen);

    return data;
}

void netResolver::compose(netHead& head, char* body, size_t bodylen, char* data)
{
    memcpy(data, &head, sizeof(netHead));
    if(body && bodylen > 0)
    {
        memcpy(data + sizeof(netHead), body, bodylen);
    }
}

netHead netResolver::getNetHead(const char *headData)
{
    netHead head;
    memcpy(&head, headData, sizeof(netHead));
    return head;
}

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