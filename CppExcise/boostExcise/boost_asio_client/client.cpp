//
// Created by wenheng on 23-3-26.
//

#include "client.h"

#include "iostream"

std::mutex s_mutex;

void client::connect()
{
    m_socket.async_connect(m_ed, boost::bind(&client::handle_connect, this, boost::asio::placeholders::error));
}

void client::handle_write()
{
    std::string line;
//    std::cout << "enter your data: ";
    std::string ip = m_socket.local_endpoint().address().to_string();
    dataInfo userinfo = netResolver::makeDataInfo(m_socket.local_endpoint().address().to_string(), m_name, time(
            nullptr));

    while(std::getline(std::cin, line) && line != "quit")
    {

        if(!m_socket.is_open())
        {
            std::cout << "write data break" << std::endl;
            exit(0);
        }
        if(line.empty())
        {
            std::cout << "please enter content..." << std::endl;
            continue;
        }
        netHead head;
        char buff[1024] = {0};
        if(line[0] != '#' && line[0] != '@')
        {
//            head.len = sizeof(playerChatMsgCmd);
//            head.type =  CHATSYS;
//            head.subtype = CHATSYS_CHATMSG;
//            head.version = 1;
//            head.checknum = netMsg::makeChceknum(head);
//            memcpy(head.info.ip, ip.data(), strlen(ip.data()));
//            memcpy(head.info.name, m_name.c_str(), strlen(m_name.c_str()));
//            head.info.times = time(nullptr);

            userinfo.times = time(nullptr);
            playerChatMsgCmd content;
            memcpy(content.buff, line.c_str(), strlen(line.c_str()));
            std::string sendbuff = netResolver::getSerializationStr(content);




            netMsg sendmsg = netResolver::makeNetMsg(sendbuff, CHATSYS, CHATSYS_CHATMSG, 1, userinfo);

            std::string sendDatas = netResolver::getSerializationStrByNetMsg(sendmsg);

//            memcpy(buff, (char*)&head, sizeof(netHead));
//            memcpy(buff + sizeof(netHead), (char*)&content, sizeof(playerChatMsgCmd));

            m_socket.write_some(boost::asio::buffer(sendDatas, sizeof(netHead) + sendmsg.head.len));
        }
        else if(line[0] == '#')
        {
            std::string findname = line.substr(1);
            if(findname == m_name)
            {
                std::cerr << "無需查找本人數據" << std::endl;
                continue;
            }

//            head.len = sizeof(playerCheckInfoCmd);
//            head.type = PLAYSYS;
//            head.subtype = PLAYSYS_CHECKPLAYERINFO_RES;
//            head.version = 1;
//            head.checknum = netMsg::makeChceknum(head);
//            memcpy(head.info.ip, ip.data(), strlen(ip.data()));
//            memcpy(head.info.name, m_name.c_str(), strlen(m_name.c_str()));
//            head.info.times = time(nullptr);

            userinfo.times = time(nullptr);

            playerCheckInfoCmd content;
            memcpy(content.name, line.substr(1).c_str(), strlen(line.substr(1).c_str()));

            std::string sendBuff = netResolver::getSerializationStr(content);
            netMsg sendmsg = netResolver::makeNetMsg(sendBuff, PLAYSYS, PLAYSYS_CHECKPLAYERINFO_RES, 1, userinfo);

            std::string sendDatas = netResolver::getSerializationStrByNetMsg(sendmsg);

//            memcpy(buff, (char*)&head, sizeof(netHead));
//            memcpy(buff + sizeof(netHead), (char*)&content, sizeof(playerCheckInfoCmd));

            m_socket.write_some(boost::asio::buffer(sendDatas, sizeof(netHead) + sendmsg.head.len));
        }
        else
        {
            std::cout << boost::format("开始查找当前在线玩家消息") << std::endl;

            userinfo.times = time(nullptr);
            playerOnlineCountCmd cmd;
            std::string  datas = netResolver::getSerializationStr(cmd);
            netMsg sendmsg = netResolver::makeNetMsg(datas, PLAYSYS, PLAYSYS_ONLINEPLAYERS, 1, userinfo);

            std::string sendDatas = netResolver::getSerializationStrByNetMsg(sendmsg);

            m_socket.write_some(boost::asio::buffer(sendDatas, sizeof(netHead) + sendmsg.head.len));
        }
    }
    m_socket.close();
    std::cout << "done!" << std::endl;

}

void client::handle_readhead(netMsgPtr ptr, boost::system::error_code ec, size_t bytes)
{
    if(ec || bytes == 0)
    {
        std::cerr << boost::format("server close...") << std::endl;
        m_socket.close();
//        exit(0);
    }
    if(!netMsg::isVaildChecknum(ptr->head))
    {
        std::cerr << "handle_readhead | head is not vaild..." << std::endl;
//        m_socket.close();
        return;

    }
    ptr->body.resize(ptr->head.len, 0);
//    std::memset(m_msg.body, 0, sizeof(m_msg.body));
    m_socket.async_read_some(boost::asio::buffer(ptr->body, ptr->head.len), \
        boost::bind(&client::handle_readbody, this, ptr, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void client::handle_readbody(netMsgPtr ptr ,boost::system::error_code ec, size_t bytes)
{
    if(ec)
    {
        std::cerr << boost::format("handle_readbody error, bytes = %d") % bytes << std::endl;
        m_socket.close();
        exit(0);
    }
    if(bytes == 0)
    {
        return;
    }


    u_short value = netMsg::maketypenum(ptr->head);
    if(value == PLAYERCHATMSG_RET)
    {
        playerChatMsgCmd_Ret ret = netResolver::getReSerializationObjByStr<playerChatMsgCmd_Ret>(ptr->body);
//        memcpy((char*)&ret, m_msg.body, sizeof(playerChatMsgCmd_Ret));

        std::cout << boost::format("[ip: %s, name: %s, time = %s] read databody(%d): %s") \
        % ptr->head.info.ip % ptr->head.info.name % netTimeResolver::getTimeString(ptr->head.info.times) % bytes % ret.buff << std::endl;
    }
    else if(value == PLAYERCHECKINFO_RET)
    {
        playerCheckInfoCmd_Ret ret = netResolver::getReSerializationObjByStr<playerCheckInfoCmd_Ret>(ptr->body);
//        memcpy((char*)&ret, m_msg.body, sizeof(playerCheckInfoCmd_Ret));

        user userInfo = ret.userInof;
        if(ret.ret == 0)
            std::cout << boost::format("查找玩家失败: %s") % userInfo.name() << std::endl;
        else
        {
            int sex = userInfo.sex();
            std::cout << boost::format("查找玩家信息成功： name = %s, sex = %d, lastloginTime = %ld") %userInfo.name() % sex \
            % netTimeResolver::getTimeString(userInfo.loginTime()) << std::endl;
        }
    }
    else if(value == PLAYERONLINECOUNT_RET)
    {
        playerOnlineCount_Ret ret = netResolver::getReSerializationObjByStr<playerOnlineCount_Ret>(ptr->body);

        if((ret.count - 1) == 0)
        {
            std::cout << "当前没有其他在线玩家" << std::endl;
        }
        else
        {
            int idx = 0;
            for(auto& user : ret.users)
            {
                std::cout << boost::format("idx: %d = [name = %s, sex = %d, loginTime = %d]") % ++idx % user.name() \
                    % user.sex() % user.loginTime() << std::endl;
            }
        }

    }
    else
    {
        int type = ptr->head.type;
        int subtype = ptr->head.subtype;
        std::cout << boost::format("未知数据包: type = %d, subtype = %d (value = %d)") % type  % subtype % value << std::endl;
    }
//    memset(m_msg.body, 0, sizeof(m_msg.body));
    netMsgPtr p2(new netMsg);
    m_socket.async_read_some(boost::asio::buffer(&(p2->head), sizeof(netHead)), boost::bind(&client::handle_readhead, this, \
        p2 , boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

bool client::handle_checkConnect()
{
    playerConnectCmd connectCmd;
    connectCmd.checkvalue = playerConnectCmd::getConnectCheckValue(connectCmd);

    user userinfo(m_name, 1);
    connectCmd.userInfo = userinfo;

    std::string datas = netResolver::getSerializationStr(connectCmd);

    dataInfo info = netResolver::makeDataInfo(m_socket.local_endpoint().address().to_string(), m_name, time(nullptr));
    netMsg msg = netResolver::makeNetMsg(datas, 1, 1, 1, info);

//    char buff[MAXBYTES] = {0};
//    memcpy(buff, (char*)&(msg.head), sizeof(netHead));

//    std::string sendBuff(sizeof(netHead) + strlen(datas.c_str()), 0);
//    memcpy(sendBuff.data(),buff, sizeof(netHead));
//    memcpy(sendBuff.data() + sizeof(netHead), datas.c_str(), strlen(datas.c_str()));
//    m_socket.write_some(boost::asio::buffer(buff, sizeof(netHead)));

    std::string sendBuff = netResolver::getSerializationStrByNetMsg(msg);

    boost::system::error_code ec;
    size_t totalLen = sizeof(netHead) + strlen(datas.c_str());
    m_socket.write_some(boost::asio::buffer(sendBuff, totalLen), ec);

    if(ec)
    {
        std::cerr << boost::format("handle_checkConnect | ec = %s") % ec.what() << std::endl;

        m_socket.close();
        return false;
    }
    char ret[1024] = {0};

//    std::string revHeadDatas(sizeof(netHead), 0);
    m_socket.read_some(boost::asio::buffer(ret, sizeof(netHead)));

    netHead gethead;
    memcpy((char*)&gethead, ret, sizeof(netHead));

    std::string revBodys(gethead.len, 0);
    m_socket.read_some(boost::asio::buffer(revBodys, gethead.len));

    playerConnectCmd_Ret revCmd = netResolver::getReSerializationObjByStr<playerConnectCmd_Ret>(revBodys);
//    playerConnectCmd_Ret retdata;
//    memcpy((char*)&retdata, ret, sizeof(playerConnectCmd_Ret));

    if(revCmd.ret == 100)
    {
        std::cerr << boost::format("客戶端連接有誤:  %s") % revCmd.msg << std::endl;
        m_socket.close();
        return false;
    }

    std::cout << "成功連接"  << std::endl;

    return true;
}

void client::handle_connect(boost::system::error_code ec)
{
    if(!ec)
    {
        using namespace boost::asio;
        if(!handle_checkConnect())
            exit(-1);
        std::cout << boost::format("connect server successfully: addr = %s") % m_socket.remote_endpoint().address().to_string() << std::endl;
//        boost::asio::async_read(m_socket, boost::asio::buffer(m_buf), boost::bind(&client::handle_read, this, placeholders::error, placeholders::bytes_transferred));

        netMsgPtr ptr(new netMsg);
        m_socket.async_read_some(boost::asio::buffer(&(ptr->head), sizeof(netHead)), boost::bind(&client::handle_readhead, this, ptr, placeholders::error, placeholders::bytes_transferred));
        std::thread t1(boost::bind(&client::handle_write, this));
        t1.detach();
    }
    else
    {
        std::cerr << boost::format("connect error, msg = %s") % ec.message() << std::endl;
        std::cerr << "reconnect again... wait for 3 secs" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        connect();
    }
}
