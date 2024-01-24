
#include "iostream"

#include "comm/commhead.h"

#include "comm/resourceManager.h"

void test_dispatch()
{
    ResourceManager manager;
    chatMessageCmd cmd;
    cmd.set_content("好想要个女朋友啊1111");
    cmd.set_status(1);
    manager.onCallMessage(&cmd);

    std::cout << getFormatStr("cmd content: %s, status: %d", cmd.content(), cmd.status()) << std::endl;
    std::string str = serlizeCmdToStr<chatMessageCmd>(cmd);
    netMsg msg(1,1, str);

    std::string sendStr = getSerlizeNetMsgStr(msg);
    
    std::cout << getFormatStr("head len = %d, body len = %d, sendStr len = %d",sizeof(netHead), msg.head.len, sendStr.size()) << std::endl;
}

void test()
{
    chatMessageCmd cmd;

    cmd.set_content("草你妈，测试测试，这是一个聊天包");
    cmd.set_status(0);

    std::string datas = serlizeCmdToStr(cmd);

    printf("datas strlen = %d, size = %d\n", strlen(datas.c_str()), datas.size());


    chatMessageCmd resolve_cmd = parseSerlizeStr<chatMessageCmd>(datas);

    printf("parseStr --->  content = %s, status = %d\n", resolve_cmd.content().c_str(), resolve_cmd.status());
}

int main(int argc, char* argv[])
{
    std::cout << "hello remote host" << std::endl;

    test();
    test_dispatch();
    return 0;
}