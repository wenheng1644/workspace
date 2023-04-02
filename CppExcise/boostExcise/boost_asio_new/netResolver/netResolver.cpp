#include "netResolver.h"
#include "memory"

netResolver* netResolver::m_ptr = nullptr;
std::mutex netResolver::m_mutex;

std::shared_ptr<char> netResolver::compose(netHead &head, char *body, size_t len)
{
//    char buff[sizeof(head) + 1] = {0};
    std::shared_ptr<char> data(new char(sizeof(head) + len + 1));
    char *p = data.get();
    char* h =  reinterpret_cast<char*>(&head);
    std::memcpy(p, h, sizeof(head));
    std::memcpy((p + sizeof(head)), body, len);

    return data;
}

std::shared_ptr<netMsg> netResolver::resolver(const char *data,  size_t len)
{
//    memcpy(&head, data, sizeof(head));
//    std::shared_ptr<char> body(new char(len));
//    memcpy(body.get(), data+sizeof(head), len);
//
//    return body;
    auto netMsg_ptr = std::shared_ptr<netMsg>(new netMsg);
    memcpy(&(netMsg_ptr->head), data, sizeof(netHead));
    memcpy(netMsg_ptr->body, data + sizeof(netHead), len - sizeof(netHead));

    return netMsg_ptr;
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
