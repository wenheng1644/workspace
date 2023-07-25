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
            playerChatMsgCmd_Ret retcmd;
            retcmd.ret = 1;
            memcpy(retcmd.buff, connectMsg.c_str(), strlen(connectMsg.c_str()));

            dataInfo info = netResolver::makeDataInfo("server", "sys", time(nullptr));
            std::string datas = netResolver::getSerializationStr(retcmd);

            netMsg msg = netResolver::makeNetMsg(datas, CHATSYS, CHATSYS_CHATMSG_RET, 1, info);
            session->deliver(msg);



            std::string content = session->name() + "进入聊天室";
            playerChatMsgCmd_Ret allCmd;
            allCmd.ret = 1;
            memcpy(allCmd.buff, content.c_str(), strlen(content.c_str()));

            std::string datas2 = netResolver::getSerializationStr(allCmd);
            netMsg allMsg = netResolver::makeNetMsg(datas2, CHATSYS, CHATSYS_CHATMSG_RET, 1, info);

            m_Room.join(session);
            m_Room.deliver(allMsg, false);

            std::cout << boost::format("name = %s 进入聊天室...") %session->name() << std::endl;

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
    CScriptSystem::getSingalton()->setCFunc<std::function<void()>>("loadNetMsg", (std::function<void()>)std::bind(&chatRoom::printMsgs, &m_Room));
    std::function<chatRoom()> f = (std::function<chatRoom()>)std::bind(&network::getRoom, this);
    CScriptSystem::getSingalton()->setCFunc<std::function<chatRoom()>>("getRoom", std::function<chatRoom()>(std::bind(&network::getRoom, this)));
}
