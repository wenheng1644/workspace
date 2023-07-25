//
// Created by wenheng on 23-4-9.
//

#include "chatRoom.h"

#include "sstream"

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"


std::mutex chatRoom::m_SessionMutex;

void chatRoom::deliver(netMsg &msg, bool isSave) {
    for(auto& session : m_Sessionqueue)
    {
        session->deliver(msg);
    }

    while(m_Msgqueue.size() >= 100)
        m_Msgqueue.pop_back();

    if(isSave)
    {
        u_short value = netMsg::maketypenum(msg.head);
        if(value == PLAYERCHATMSG_RET)
            m_Msgqueue.push_back(std::shared_ptr<netMsg>(new netMsg(msg)));
    };
}

void chatRoom::join(chatSessionPtr session)
{
    if(m_Sessionqueue.count(session))
        return;
    {
        std::lock_guard<std::mutex> gl(m_SessionMutex);
        m_Sessionqueue.insert(session);
    }

//    std::cout << boost::format("m_msgqueue size = %d") % m_Msgqueue.size() << std::endl;
    sendOnlineCountMsg();
    for(auto& msg : m_Msgqueue)
        session->deliver(*msg);
}

bool chatRoom::leave(chatSessionPtr session)
{
    if(!m_Sessionqueue.count(session))
        return false;

    {
        std::lock_guard<std::mutex> gl(m_SessionMutex);
        m_Sessionqueue.erase(session);
    }
    sendOnlineCountMsg();
    return true;
}

chatRoom::chatRoom(const std::vector<netMsg> &netMsgs)
{
    for(netMsg msg : netMsgs)
    {
        std::shared_ptr<netMsg> ptr(new netMsg);
        ptr->head.len = msg.head.len;
        ptr->head.type = msg.head.type;
        ptr->head.subtype = msg.head.subtype;
        ptr->head.version = msg.head.version;
        ptr->head.checknum = msg.head.checknum;
        ptr->head.info.times = msg.head.info.times;
        memcpy(ptr->head.info.ip, msg.head.info.ip, sizeof(msg.head.info.ip));
        memcpy(ptr->head.info.name, msg.head.info.name, sizeof(msg.head.info.name));
//        memcpy(ptr->body, msg.body, sizeof(msg.body));

        ptr->body = msg.body;
        m_Msgqueue.push_back(ptr);
    }


    std::thread roomRunThread(&chatRoom::runChatSession, this);
    roomRunThread.detach();
}

void chatRoom::writeToFile()
{
    CScriptSystem *lua = CScriptSystem::getSingalton();
    netMsgList netMsgs;

    for(const auto& ptr : m_Msgqueue)
    {
        netMsgs.push_back(*ptr);
    }
    lua->clua_wirtefile(netMsgs);
    std::cout << "chatRoom::writeToFile | write to file done" << std::endl;
}

void chatRoom::printMsgs()
{
    for(const auto& data : m_Msgqueue)
    {
        netMsg msg = *data;
        playerChatMsgCmd_Ret ret = netResolver::getReSerializationObjByStr<playerChatMsgCmd_Ret>(msg.body);


        std::cout << boost::format("[time = %s, name = %s, ip = %s] = %s") % netTimeResolver::getTimeString(msg.head.info.times) %
            msg.head.info.name % msg.head.info.ip %
            ret.buff << std::endl;
    }
}

void chatRoom::deliver(const std::string &name, netMsg &msg)
{
    auto p = std::find_if(m_Sessionqueue.begin(), m_Sessionqueue.end(), [name](chatSessionPtr a)
    {
        if(a->name() == name) return true;
        return false;
    });

    if(p == m_Sessionqueue.end())
    {
        std::cout << boost::format ("can't find user[%s]") % name << std::endl;
        return;
    }

    chatSessionPtr session = *p;
    session->deliver(msg);
}

std::shared_ptr<chatSession> chatRoom::findChatSeesion(const std::string &name)
{
    auto lam = [name](std::shared_ptr<chatSession> session){
        if(session->name() == name)
            return true;
        return false;
    };

    auto iter = std::find_if(m_Sessionqueue.begin(), m_Sessionqueue.end(), lam);

    if(iter != m_Sessionqueue.end())
        return *iter;

    return std::shared_ptr<chatSession>();
}

void chatRoom::runChatSession()
{
    std::cout << boost::format("runChatSession | 線程id = %d, 開始執行") % std::this_thread::get_id() << std::endl;
    while(true)
    {
        std::lock_guard<std::mutex> gl(m_SessionMutex);
        for(auto session : m_Sessionqueue)
        {
            session->runNetMsg();
        }
    }
}

void chatRoom::sendOnlineCountMsg()
{
    playerOnlineCount_Ret sendRet;

    for(const auto& session : m_Sessionqueue)
    {
        user userinfo = session->getuserinfo();
        sendRet.users.push_back(userinfo);
        sendRet.count += 1;
    }
    size_t userLen = sizeof(user);
    size_t userslen = sizeof(sendRet.users);
    size_t orginlen = sizeof(std::deque<user>);
    size_t shortlen = sizeof(short);
    size_t retcmdlen = sizeof(playerOnlineCount_Ret);
//    size_t extraLen = sendRet.count * sizeof(sendRet.users)
    netMsg msg = netResolver::generator()->makeNetMsg((char*)&sendRet, sizeof(playerOnlineCount_Ret), \
        PLAYSYS, PLAYSYS_ONLINEPLAYERS_RET);

    deliver(msg);
}

void chatSession::start()
{
    std::shared_ptr<netMsg> p(new netMsg);
    m_sessionSocket.async_read_some(boost::asio::buffer(&(p->head), sizeof(netHead)), \
        boost::bind(&chatSession::handle_readhead, shared_from_this(), p, \
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void chatSession::deliver(netMsg &msg)
{
    using namespace boost::asio;
//    char buff[MAXBYTES] = {0};
//    netHead head;
    std::string sendBuff = netResolver::getSerializationStrByNetMsg(msg);

    m_sessionSocket.async_write_some(boost::asio::buffer(sendBuff, sizeof(netHead) + msg.head.len), boost::bind(&chatSession::handle_write, shared_from_this(), \
        placeholders::error, placeholders::bytes_transferred));
}

void chatSession::handle_readhead(std::shared_ptr<netMsg> p, error_code_type ec, size_t bytes)
{
    using namespace boost::asio;

    if(ec || bytes == 0)
    {
        std::cerr << boost::format ("连接断开 | ec = %s bytes = %d") % ec.what() % bytes << std::endl;
        m_Room.leave(shared_from_this());
        m_sessionSocket.close();

        return;
    }

    if(!netMsg::isVaildChecknum(p->head))
    {
        std::cerr << "handle_readhead | not a vaild msg" << std::endl;
        return;
    }
    //重置缓存大小
    p->body.resize(p->head.len, 0);
    m_sessionSocket.async_read_some(boost::asio::buffer(p->body, p->head.len), boost::bind(&chatSession::handle_readbody, shared_from_this(), \
        p, placeholders::error, placeholders::bytes_transferred));
}

void chatSession::handle_readbody(std::shared_ptr<netMsg> p, error_code_type ec, size_t bytes)
{
    if(ec)
    {
        std::cerr << "handle_readbody | ec" << std::endl;
        return;
    }

    {
        std::lock_guard<std::mutex> gl(m_NetMsgMutex);
        m_dataNetMsg.push_back(p);
    }
//    onHandleMsg(*p);

    std::shared_ptr<netMsg> p2(new netMsg);
    m_sessionSocket.async_read_some(boost::asio::buffer(&(p2->head), sizeof(netHead)), \
        boost::bind(&chatSession::handle_readhead, shared_from_this(), p2, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void chatSession::handle_write(error_code_type ec, size_t bytes)
{
    if(ec)
    {
        std::cout << boost::format("handle_write error, bytes = %d") % bytes << std::endl;
        return;
    }
}

bool chatSession::isVaildConnect()
{
    boost::system::error_code ec;
    size_t needGetBytes = sizeof(netHead);
    std::string revHeadBuff(needGetBytes, 0);
    char buff[MAXBYTES] = {0};
    size_t bytes = m_sessionSocket.read_some(boost::asio::buffer(buff, needGetBytes), ec);

    netHead head;
    memcpy((char*)&head, buff, sizeof(netHead));

//    netHead head = netResolver::getReSerializationObjByStr<netHead>(revHeadBuff);

    std::string datas(head.len, 0);

    m_sessionSocket.read_some(boost::asio::buffer(datas, head.len), ec);
    char ret[1024] = {0};
    playerConnectCmd_Ret retcmd;

    std::string msg;
    if(ec)
    {
        std::cerr << "isVaildConnect error" << std::endl;

        retcmd.ret = 100;

        sendConnectRetMsg(retcmd, "连接失败");

        m_sessionSocket.close();
        return false;
    }

    if(bytes == 0 || bytes != needGetBytes)
    {
        std::cerr << boost::format("pre socket has done..., bytes = %d") % bytes << std::endl;

        retcmd.ret = 100;

        sendConnectRetMsg(retcmd, "传送字节数有误");
        m_sessionSocket.close();
        return false;
    }



    if(!netMsg::isVaildChecknum(head))
    {
        std::cerr << boost::format("netMsg校驗失敗") << std::endl;

        retcmd.ret = 100;

        sendConnectRetMsg(retcmd, "netMsg校验失败");
        m_sessionSocket.close();
        return false;
    }

    u_short value = netMsg::maketypenum(head);

    if(value != PLAYERCONNECT)
    {
        int type = head.type;
        int subtype = head.subtype;
        std::cerr << boost::format("登錄包有誤....  value = %d, type = %d, subtype = %d") % value \
        % type % subtype << std::endl;

        retcmd.ret = 100;

        sendConnectRetMsg(retcmd, "登录包value有误");
        m_sessionSocket.close();
        return false;
    }

//    memcpy(p->body, buff + sizeof(netHead), sizeof(playerConnectCmd));

    playerConnectCmd cmd = netResolver::getReSerializationObjByStr<playerConnectCmd>(datas);


    if(!cmd.isvaild())
    {
        int v1 = cmd.v1;
        int v2 = cmd.v2;
        int v3 = cmd.v3;

        int checkvnum = cmd.checkvalue;
        std::cerr << boost::format("登錄包校驗失敗: v1 = %d, v2 = %d, v3 = %d, checkvnum = %d") % v1\
        % v2 % v3 % checkvnum << std::endl;

        retcmd.ret = 100;

        sendConnectRetMsg(retcmd, "登录包校验码有误");
        m_sessionSocket.close();

        return false;
    }

    setname(head.info.name);
    if(CScriptSystem::getSingalton()->loadLuaGM("IsBanUserTb", m_user.name()))
    {
        retcmd.ret = 100;

        sendConnectRetMsg(retcmd, "用户被封: 请联系管理员");

        m_sessionSocket.close();

        return false;
    };

    retcmd.ret = 1;

    user userinfo = cmd.userInfo;

    std::cout << boost::format("成功連接:  username = %s, sex = %d, logintime = %d") % userinfo.name().c_str() \
        % userinfo.sex() % userinfo.loginTime() << std::endl;

    sendConnectRetMsg(retcmd, "成功连接");
    return true;
}

bool chatSession::close()
{
    if(!m_sessionSocket.is_open()) return false;

    m_Room.leave(shared_from_this());
    m_sessionSocket.close();

    return true;
}

//void chatSession::onPlayConnectMsg(const netMsg &msg)
//{
//    u_short value = netMsg::maketypenum(msg.head);
//    if(value != PLAYERCONNECT)
//        return;
//
//    char buff[sizeof(playerConnectCmd)] = {0};
//
//    memcpy(buff, msg.body, sizeof(playerConnectCmd));
//
//    playerConnectCmd* cmd = static_cast<playerConnectCmd*>((void*)buff);
//
//    if(!cmd->isvaild())
//    {
//        std::cerr << boost::format("连接包非法") << std::endl;
//        m_Room.leave(shared_from_this());
//        close();
//        return;
//    }
//
//    std::cout << "连接包正确: 成功" << std::endl;
//}

void chatSession::onPlayChatMsg(const netMsg &msg)
{
    u_short value = netMsg::maketypenum(msg.head);
    if(value != PLAYERCHATMSG)
    {
        return;
    }
    playerChatMsgCmd cmd = netResolver::getReSerializationObjByStr<playerChatMsgCmd>(msg.body);

    std::cout << boost::format("收到消息[timezone (%d)]: %s") % msg.head.info.times % cmd.buff << std::endl;

    playerChatMsgCmd_Ret retCmd;
    retCmd.ret = 1;
    memcpy(retCmd.buff, cmd.buff, sizeof(cmd.buff));

    std::string datas = netResolver::getSerializationStr(retCmd);

    dataInfo info = msg.head.info;
    netMsg chatmsg = netResolver::makeNetMsg(datas, CHATSYS, CHATSYS_CHATMSG_RET, 1, info);

    m_Room.deliver(chatmsg);
}

void chatSession::onPlayCheckInfo(const netMsg &msg)
{
    u_short value = netMsg::maketypenum(msg.head);
    if(value != PLAYERCHECKINFO)
        return;

    playerCheckInfoCmd cmd = netResolver::getReSerializationObjByStr<playerCheckInfoCmd>(msg.body);

    std::string checkname(cmd.name);
    playerCheckInfoCmd_Ret retcmd;
    retcmd.ret = 0;

    auto lam = [checkname](std::shared_ptr<chatSession> session){
        if(session->name() == checkname) return true;
        return false;
    };
    auto iter = std::find_if(m_Room.m_Sessionqueue.begin(), m_Room.m_Sessionqueue.end(), lam);

    retcmd.userInof = user((cmd.name));

    if(m_Room.findChatSeesion(cmd.name))
    {
        retcmd.ret = 1;
        retcmd.userInof = (*iter)->getuserinfo();
    }

    std::string datas = netResolver::getSerializationStr(retcmd);
    netMsg chatmsg = netResolver::makeNetMsg(datas, PLAYSYS, PLAYSYS_CHECKPLAYERINFO_RET, 1, msg.head.info);

    deliver(chatmsg);
}

void chatSession::onPlaySendUserChat(const netMsg &msg)
{
    u_short value = netMsg::maketypenum(msg.head);
    if(value != PLAYERSENDUSERCHAT)
        return;

    playerSendUserChatCmd cmd = netResolver::getReSerializationObjByStr<playerSendUserChatCmd>(msg.body);

    playerSendUserChatCmd_Ret retcmd;
    retcmd.ret = 1;
    std::shared_ptr<chatSession> target = m_Room.findChatSeesion(cmd.name);
    if(!target)
    {
        retcmd.ret = 0;
        memcpy(retcmd.content, "没有该玩家", strlen("没有该玩家"));
    }

    std::string datas = netResolver::getSerializationStr(retcmd);
    netMsg sendMsg = netResolver::makeNetMsg(datas, CHATSYS, PLAYERSENDUSERCHAT_RET, 1, msg.head.info);

    deliver(sendMsg);
}

void chatSession::onPlayOnlineCountUser(const netMsg &msg)
{
    u_short value = netMsg::maketypenum(msg.head);
    if(value != PLAYERONLINECOUNT)
        return;

    playerOnlineCount_Ret ret;

//    std::lock_guard<std::mutex> gl(m_Room.m_SessionMutex);
    ret.count = 0;
    for(auto& session : m_Room.m_Sessionqueue)
    {
        ret.users.push_back(session->getuserinfo());
        ret.count += 1;
    }

    std::string datas = netResolver::getSerializationStr(ret);

    netMsg sendmsg = netResolver::makeNetMsg(datas, PLAYSYS, PLAYSYS_ONLINEPLAYERS_RET, 1, msg.head.info);

    deliver(sendmsg);
}


void chatSession::onHandleMsg(const netMsg &msg)
{
    u_short value = netMsg::maketypenum(msg.head);
    int type = msg.head.type;
    int subtype = msg.head.subtype;
    switch (value) {
        case PLAYERCHATMSG:
            onPlayChatMsg(msg);
            break;
        case PLAYERCHECKINFO:
            onPlayCheckInfo(msg);
            break;
        case PLAYERSENDUSERCHAT:
            onPlaySendUserChat(msg);
            break;
        case PLAYERONLINECOUNT:
            onPlayOnlineCountUser(msg);
            break;
        default:
            std::cerr << boost::format("未定义包数据 value = %d, [type = %d, subtype = %d]") % value \
               % type % subtype << std::endl;
            break;
    }
}

void chatSession::sendConnectRetMsg(playerConnectCmd_Ret &cmd, const std::string &conntent)
{
    memcpy(cmd.msg, conntent.c_str(), strlen(conntent.c_str()));
    std::string datas = netResolver::getSerializationStr<playerConnectCmd_Ret>(cmd);
    netMsg msg = netResolver::makeNetMsg(datas, PLAYSYS, PLAYSYS_LOGIN_RET);

    deliver(msg);
}

void chatSession::sendNetMsg(const netMsg &msg)
{
    size_t bytes = sizeof(netHead) + msg.head.len;

    char buff[1024] = {0};
    memcpy(buff, (char*)&msg, bytes);

    m_sessionSocket.write_some(boost::asio::buffer(buff, bytes));
}

void chatSession::runNetMsg()
{
    std::lock_guard<std::mutex> gl(m_NetMsgMutex);
    while(!m_dataNetMsg.empty())
    {
        auto msg = m_dataNetMsg.front();
        onHandleMsg(*msg);
        m_dataNetMsg.pop_front();
    }
}

bool chatSession::test_vaildConnect()
{
    char buff[1024] = {0};
    boost::system::error_code ec;
    m_sessionSocket.read_some(boost::asio::buffer(buff, sizeof(netHead)), ec);

    if(ec)
    {
        std::cerr << boost::format("ec = %s") %ec.what() << std::endl;
        return false;
    }

    netHead head;
    memcpy((char*)&head, buff, sizeof(netHead));

    std::string str(head.len, 0);

    m_sessionSocket.read_some(boost::asio::buffer(str, head.len));

    playerConnectCmd ret = netResolver::getReSerializationObjByStr<playerConnectCmd>(str);

//    std::istringstream ss(str);
//    boost::archive::text_iarchive ia(ss);
//
//    playerConnectCmd ret;
//
//    ia >> ret;


    return true;
}





