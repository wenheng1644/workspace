//
// Created by нд╨Ц on 2022/7/12.
//

#include "myWinSock.h"
#include "iostream"
#include "thread"

void myWinSock::set_sockstate()
{
    WSADATA data;
    if(0 != WSAStartup(MAKEWORD(2,2), &data))
    {
        printf("startup error\n");
        exit(-1);
    }

    printf("start up successfully~\n");
}

void myWinSock::clean_exit()
{
    WSACleanup();
    exit(0);
}

void myWinSock::start()
{
    SOCKET listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(INVALID_SOCKET == listenfd)
    {
        clean_exit();
    }

    sockaddr_in bind_addr;
    bind_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    bind_addr.sin_port = htons(8888);
    bind_addr.sin_family = AF_INET;

    if(SOCKET_ERROR == bind(listenfd, (sockaddr *)&bind_addr, sizeof bind_addr))
        clean_exit();

    if(SOCKET_ERROR == listen(listenfd, SOMAXCONN))
        clean_exit();

    sockaddr_in client_addr;
    int len = sizeof client_addr;
    SOCKET clientfd = accept(listenfd,(sockaddr *)&client_addr, &len);

    if(INVALID_SOCKET == clientfd)
        clean_exit();

    char buf[] = "hello world\n";
    for(int i = 0; i < 5; i++)
    {
        send(clientfd, buf, sizeof buf, 0);
    }

    closesocket(clientfd);
    closesocket(listenfd);

}

void myWinSock::gethostInfo()
{
    sockaddr_in addr;
    addr.sin_port = htons(8888);
    addr.sin_family = AF_INET;
    addr.sin_addr.S_un.S_addr = inet_addr("121.37.233.74");


    hostent* p = gethostbyaddr((char *)&addr.sin_addr, 4, AF_INET);
    if(p)
    {
        std::cout << "offical name = " << p->h_name << std::endl;
    }
}
