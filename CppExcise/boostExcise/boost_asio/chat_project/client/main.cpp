//
// Created by ???? on 2022/4/12.
//
#pragma execution_character_set("utf-8")

#include "client.h"
#include "../server/dateTimeMgr.h"
#include "code_convert.h"
#include "thread"
#include "cstring"
#include "locale"


#include "boost/asio.hpp"

using namespace boost::asio;

int main()
{
//    system("chcp 65001");
//    std::locale::global(std::locale("chs"));
    if(!setlocale(LC_ALL,""))
        std::cout << "set error" << std::endl;
    try
    {
        boost::asio::io_service io_service;

        ip::tcp::resolver resolver(io_service);
        ip::tcp::resolver::query query("121.0.0.1", "8080"); // ip port:¡À??¨²
        ip::tcp::resolver::iterator iterator = resolver.resolve(query);

        chat_client c(io_service, iterator); // ????????????

        std::thread t(boost::bind(&boost::asio::io_service::run, &io_service)); // ????

        char line[BODY_LEN + 1];

        std::string username_str("xwh");
        ///???¡ì???¨°???¨¬??¡¤??????????????¨¹??????
        std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;
        while (std::cin.getline(line, BODY_LEN + 1))
        {
//            char sendmsg[BODY_LEN] = {};
//            size_t dateTimeLen = strlen(dateTimeMgr::getDateTime().c_str());
//            memcpy(sendmsg, dateTimeMgr::getDateTime().c_str(), dateTimeLen);
//            strcat(sendmsg, line);

            char sendmsg[BODY_LEN + 1] = {};
            memset(sendmsg, ' ', USERNAME_LEN);
            memcpy(sendmsg, username_str.c_str(),strlen(username_str.c_str()));
            strcat(sendmsg + USERNAME_LEN, line);
            std::string sendmsg_str(sendmsg);
//            std::cout << "data: " << sendmsg_str << std::endl;
//            std::cout << coding::utf8_to_gbk(sendmsg_str) << std::endl;
            chatMsg msg;
            msg.bodyLen(strlen(sendmsg));
            memcpy(msg.body(), sendmsg_str.data(), msg.bodyLen());// line to msg
            msg.encode();
            c.write(msg);
        }

        c.close();
        t.join(); // ????????
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}