//
// Created by wenheng on 23-3-25.
//

#include "network.h"

void network::run() {
    using namespace boost::system;
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

network::network(boost::asio::io_service &ioserver, tcp::endpoint ed, std::vector<netMsg> netMsgs) : m_acceptor(ioserver, ed) \
     , m_ioserver(ioserver), m_Room(netMsgs), m_timer(ioserver)
{
//    m_Room = chatRoom(netMsgs);
    m_timer.start(std::bind(&chatRoom::writeToFile, &m_Room) , std::chrono::seconds(60), -1);
    lua_loadFunc();
}

network::~network()
{

    std::cout << "close to save netMsg Records..." << std::endl;
    m_Room.writeToFile();
    std::cout << "network is deleted...." << std::endl;
}

void network::writeToFile()
{

}

void network::stop()
{
    if(!m_acceptor.is_open())
    {
        std::cout << "is not open" << std::endl;
        return;
    }

    error_code_type ec;
    m_acceptor.close(ec);
    m_ioserver.stop();

    if(ec)
    {
        std::cout << "close server error: " << ec.what() << std::endl;
        exit(-1);
    }

    std::cout << "server close successfully!" << std::endl;
}

void network::lua_loadFunc()
{
//    sol::state& lua = CScriptSystem::getSingalton()->getLua_State();
//
//    lua.set_function("loadNetMsg", (std::function<void()>)std::bind(&chatRoom::printMsgs, &m_Room));
//    lua.set_function("getRoom", (std::function<chatRoom()>)std::bind(&network::getRoom, this));
    CScriptSystem::getSingalton()->setCFunc<std::function<void()>>("loadNetMsg", (std::function<void()>)std::bind(&chatRoom::printMsgs, &m_Room));
    CScriptSystem::getSingalton()->setCFunc<std::function<chatRoom()>>("getRoom", (std::function<chatRoom()>)std::bind(&network::getRoom, this));
    CScriptSystem::getSingalton()->setCFunc<std::function<void()>>("printSessionInfo", (std::function<void()>)std::bind(&chatRoom::printSession, &m_Room));
}
