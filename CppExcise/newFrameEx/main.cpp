
#include "iostream"

#include "comm/commhead.h"

void test()
{
    chatMessageCmd cmd;

    cmd.set_content("草你妈，测试测试，这是一个聊天包");
    cmd.set_status(0);

    std::string datas = serlizeCmdToStr(&cmd);

    printf("datas strlen = %d, size = %d\n", strlen(datas.c_str()), datas.size());


    chatMessageCmd resolve_cmd = parseSerlizeStr<chatMessageCmd>(datas);

    printf("parseStr --->  content = %s, status = %d\n", resolve_cmd.content().c_str(), resolve_cmd.status());
}

int main(int argc, char* argv[])
{
    std::cout << "hello remote host" << std::endl;

    test();
    return 0;
}