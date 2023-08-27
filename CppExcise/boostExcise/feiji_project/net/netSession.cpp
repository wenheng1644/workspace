//
// Created by wenheng on 23-6-24.
//

#include "boost/format.hpp"

#include "netSession.h"
#include "chat_cmd.h"
#include "playerInfo_cmd.h"

bool netSession::operator<(const netSession &v) const
{
    if(m_onlyid < v.m_onlyid)
        return true;
    return false;
}

bool netSession::operator==(const netSession &v) const
{
    if(this != &v) return false;
    if(m_onlyid != v.m_onlyid) return false;

    return true;
}

void netSession::operate(bCmd *cmd)
{
    if(!cmd) return;

    using boost::format;
    u_short value = MAKEVALUE(cmd->id, cmd->subid);
    switch (value) {

        case PLAYERINFO_VALE:
        {
            playerInfoCmdRes* p = ((playerInfoCmdRes*)cmd);
            if(p)
            {
                std::cout << format("[玩家信息] ip = %s\nport = %d\nname = %s\ntime = %ld")
                             % p->ip % p->port % p->sendname % p->t << std::endl;

                delete p;
            }
        }
        case CHATRES_VALUE:
        {
            chatCmdRes* p = (chatCmdRes*)cmd;
            if(p)
            {
                std::cout << format("[玩家发送消息: ] %s") % p->content << std::endl;

                delete p;
            }
        }
        default:
        {
            std::cerr << format("解包失败.... value = %d") % value << std::endl;
            delete cmd;
        }
    }
}
