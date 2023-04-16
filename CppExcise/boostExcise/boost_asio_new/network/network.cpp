//
// Created by wenheng on 23-3-25.
//

#include "network.h"

void network::run() {
    using namespace boost::system;
    std::cout << "start to listen" << std::endl;
    chatSessionPtr session_ptr(new chatSession(m_ioserver, m_Room));
    m_acceptor.async_accept(session_ptr->socket(), boost::bind(&network::handle_accept, this, session_ptr, boost::asio::placeholders::error));

}

void network::handle_accept(chatSessionPtr session, error_code_type ec)
{
    if(!ec)
    {
        if(session->isVaildConnect())
        {
            std::string connectMsg = "thank you connect the server!!!";
            netHead head;
            head.len = strlen(connectMsg.data());
            head.type = 1;
            head.version = 0;
            head.checknum = netMsg::makeChceknum(head);
            head.info.times = std::time(nullptr);
            memcpy(head.info.name, "sys", 3);
            memcpy(head.info.ip, "server", 6);
            char buff[1024] = {0};
            netResolver::generator()->compose(head, connectMsg.data(), head.len, buff);
            auto msg_ptr = netResolver::generator()->resolver(buff, sizeof(netHead) + head.len);
            session->deliver(*msg_ptr);
            session->start();
        }
    }
    run();
}
//
//void Room::deliver(netMsg &msg) {
//    for (auto session: m_Sessionqueue) {
//        session->deliver(msg);
//    }
//
//    while(m_Msgqueue.size() >= 100)
//    {
//        m_Msgqueue.pop_back();
//    }
//    m_Msgqueue.push_back(std::shared_ptr<netMsg>(new netMsg(msg)));
//}
//
//void Room::join(std::shared_ptr<Session> session) {
//    if(m_Sessionqueue.count(session))
//        return;
//    m_Sessionqueue.insert(session);
//    std::cout << boost::format("m_Msgqueue size = %d") % m_Msgqueue.size() << std::endl;
//    int index = 0;
//    for (std::shared_ptr<netMsg> msg: m_Msgqueue) {
//        std::cout << boost::format("index(%d): msg = %s") % (++index) % msg->body << std::endl;
//        session->deliver(*msg);
//    }
//}
//
//void Room::leave(std::shared_ptr<Session> session) {
//    if(m_Sessionqueue.empty())
//        return;
//
//    if(!m_Sessionqueue.count(session))
//        return;
//
//    m_Sessionqueue.erase(session);
//}
