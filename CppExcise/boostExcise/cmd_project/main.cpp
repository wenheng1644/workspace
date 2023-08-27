#include <iostream>

#include "cmd/base_cmd.h"
#include "cmd/user_cmd.h"

#include "thread"

#include "threadPool/threadPool.h"
int main() {

//    userLoginCmd cmd;
//    cmd.m_sex = 1;
//    cmd.m_time = time(nullptr);
//    cmd.m_name = "xwz";
//
//    netData datas = netQtResolver::getNetDataByCmd(cmd);
//
//    printf("str = %s, len = %d\n", datas.first.c_str(), datas.second);
//
//    userLoginCmd cmd222 = netQtResolver::getCmdByNetData<userLoginCmd>(datas);
//
//    printf("name = %s, sex = %d, time = %d, type = %d, subtype = %d\n", cmd222.m_name.c_str(), cmd222.m_sex, \
//        u_int(cmd222.m_time), cmd222.type, cmd222.subtype);
//
//    std::cout << "hello" << std::endl;
//
//    userChatCmd cmd_chat;
//    cmd_chat.m_sex = 1;
//    cmd_chat.m_name = "xwz";
//    cmd_chat.m_time = time(nullptr);
//    cmd_chat.m_content = "你好， 世界， 爱你";
//
//    netData chat_Data = netQtResolver::getNetDataByCmd(cmd_chat);
//    printf("chat_Data | str = %s, len = %d\n", chat_Data.first.c_str(), chat_Data.second);
//
//    userChatCmd cmd_chat222 = netQtResolver::getCmdByNetData<userChatCmd>(chat_Data);

    std::cout << "并发线程数 = " << std::thread::hardware_concurrency() << std::endl;
    threadPool pool;

//    std::thread createT(&createThread, std::ref(pool));
    pool.run();

    createThread(pool);

    return 0;
}
