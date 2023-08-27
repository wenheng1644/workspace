//
// Created by wenheng on 23-3-25.
//

#include "network/network.h"
#include "netResolver/netResolver.h"
#include "netQtResolver.h"
#include "CScriptSystem/CScriptSystem.h"
#include "boost/asio/steady_timer.hpp"

#include "QtCore/QDataStream"
#include "QtCore/QIODevice"
#include "QtCore/QByteArray"
#include "QtCore/QBuffer"

#include "regex"
#include "thread"
#include "string"
#include "cstring"

#include <signal.h>
#include <unistd.h>
#include <execinfo.h>
#include <fcntl.h>


//void test() {
//    netResolver *resolver = netResolver::generator();
//    char body[] = "hello linux";
//    netHead head;
//    head.len = sizeof(body);
//    std::shared_ptr<char> data = resolver->compose(head, body, sizeof body);
//
//    char buff[1024] = {0};
//    char *ptr = data.get();
//    memcpy(buff, ptr, sizeof(head) + sizeof(body) + 1);
//    std::cout << "data = " << data << std::endl;
//}

void checkSize()
{
    std::string str1("hello world");
    std::string str2("你好 世界!");

    std::cout << boost::format("str1 bytes = %d, str2 bytes = %d") % strlen(str1.c_str()) % strlen(str2.c_str()) << std::endl;
}

void inputThread(network* net)
{
    std::string line;
    std::cout << "inputThread | coming" << std::endl;
    while(true)
    {
        std::getline(std::cin, line);
        if(line == "quit")
        {
            net->stop();
            break;
        }

        if(line[0] == '@')
        {
            CScriptSystem *lua = CScriptSystem::getSingalton();
            if(line == "@reload")
            {
                lua->load();
                net->lua_loadFunc();
                std::cout << "###reload lua successfully" << std::endl;
            }
            else
            {
//                std::string funcname = line.substr(1);
                line = line.substr(1);
                std::vector<std::string> strs;
                std::regex partten("[^\\s]+");
                std::sregex_iterator next(line.begin(), line.end(), partten);
                std::sregex_iterator end;
                while(next != end)
                {
                    std::smatch match = *next;
                    next++;
                    strs.push_back(match.str());
                }

                int paramSize = strs.size();
                if(paramSize >= 1)
                {
                    std::string funcname = strs[0];
                    switch (paramSize)
                    {
//                        bool isExec;
                        case 1:
                            if(lua->loadLuaGM(funcname))
                            {
                                std::cout << boost::format("###dolua %s successfully") % funcname << std::endl;
                            }
                            break;
                        case 2:
                        {
                            if(lua->loadLuaGM(funcname, strs[1]))
                            {
                                std::cout << boost::format("###dolua %s(%s) successfully") % funcname % strs[1] << std::endl;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(lua->loadLuaGM(funcname, strs[1], strs[2]))
                            {
                                std::cout << boost::format("###dolua %s(%s, %s) successfully") % funcname % strs[1] % strs[2] << std::endl;
                            }
                            break;
                        }
                        default:
                        {
                            std::cout << "没有适配函数，请检查" << std::endl;
                            break;
                        }
                    }


                }
                else
                    std::cerr << boost::format("###dolua fail") << std::endl;
            }
        }
        else
        {
            std::cout << "invaild input" << std::endl;
        }


    }
}

void handler_signal(int signal_)
{
    const char* dumpFile = "./log/crash_dump.dmp";

    // 创建Dump文件
    int fd = open(dumpFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd != -1)
    {
        // 获取调用栈信息
        void* callstack[128];
        int frames = backtrace(callstack, sizeof(callstack) / sizeof(void*));
        backtrace_symbols_fd(callstack, frames, fd);

        close(fd);
    }

    // 继续执行默认的信号处理
    signal(signal_, SIG_DFL);
    raise(signal_);
}

void test_newCmd()
{
    playcheckLoginCmd cmd;
    user userinfo("xwz");
    cmd.userinfo = userinfo;

    std::string datas = netResolver::getSerializationStr(cmd);

    playcheckLoginCmd cmd2 = netResolver::getReSerializationObjByStr<playcheckLoginCmd>(datas);

    std::cout << boost::format("(data size = %d)type = %d, subtype = %d, username = %s, sex = %d") % datas.length() % (int)cmd2.type
        % (int)cmd2.subtype % cmd2.userinfo.name() % int(cmd2.userinfo.sex()) << std::endl;
}

void test_QtDataStream()
{

    playcheckLoginCmd cmd;
    user userinfo("xwz");
    cmd.userinfo = userinfo;

    user userinfo1("xzy");
    cmd.userinfo = userinfo;

    user userinfo2("khx");
    cmd.userinfo = userinfo;

    cmd.otherUsers.push_back(userinfo1);
    cmd.otherUsers.push_back(userinfo2);

    netStrData netData = netQtResolver::getSerialStrByCmdData(cmd);

    std::cout << boost::format("serStr = %s, len = %d") % netData.first % netData.second << std::endl;

    playcheckLoginCmd getCmd = netQtResolver::getCmdDataBySerStr<playcheckLoginCmd>(netData);



    std::cout << "ok";
}

int main(int argc, char *argv[]) {
    signal(SIGSEGV, handler_signal);
    signal(SIGABRT, handler_signal);

//    playcheckLoginCmd cmd;
//
//    std::cout << boost::format("当前cmd type = %d, subtype = %d") % int(cmd.type) % int(cmd.subtype) << std::endl;
//
    CScriptSystem *lua = CScriptSystem::getSingalton();

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//    std::deque<netMsg> netMsgs;
//    int t = 0;
//    for(int i = 0; i < 5; i++)
//    {
//        netHead ptr;
//        ptr.type = 1;
//        ptr.len = sizeof("what the fuck?");
//        ptr.version = 1;
//        ptr.checknum = netMsg::makeChceknum(ptr);
//        memcpy(ptr.info.ip, "127.0.0.1", sizeof("127.0.0.1"));
//        memcpy(ptr.info.name, "xwz", 3);
//        ptr.info.times = t++;
//        netMsg msg;
//        msg.head = ptr;
//        memcpy(msg.body, "what the fuck?", sizeof("what the fuck?"));
//
//        netMsgs.push_back(msg);
//    }
//    lua->clua_wirtefile(netMsgs);
//    lua->test_toLua(msg);
//
//    lua->clua_wirtefile(msg);
//    lua->clua_wirtefile()

//***************************************************
    std::vector<netMsg> netMsgs = lua->loadNetMsg();
     if(argc != 2)
     {
         std::cerr << "arg count error" << std::endl;
         exit(-1);
     }
     std::cout << "*argv[0] = " << (argv[0]) << std::endl;
     std::cout << "*argv[1] = " << (argv[1]) << std::endl;
     u_short port = std::stoi(std::string(argv[1]));
     std::cout << "port = " << port << std::endl;
     boost::asio::io_service ioserver;

     using namespace boost::asio;

     //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//    time_with_func timers(ioserver, 5, [](){
//       std::cout << "hello world" << std::endl;
//    });
//
//***********************************************
     boost::asio::ip::tcp::endpoint  ed(boost::asio::ip::address::from_string("192.168.1.6"), port);
     std::cout << "addr = " << ed.address().to_string() << std::endl;
     network net(ioserver, ed, netMsgs);
     std::cout << "start to listen" << std::endl;
     net.run();

     std::thread t2(inputThread, &net);
     t2.detach();

     ioserver.run();

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2

    return 0;
}