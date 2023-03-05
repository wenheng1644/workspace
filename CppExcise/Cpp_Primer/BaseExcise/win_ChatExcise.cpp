//
// Created by нд╨Ц on 2022/10/2.
//
#include "win_ChatExcise.h"

SOCKET g_clients[STRLEN_MAX];
int g_clientCnt = 0;

HANDLE g_SerMutex;

unsigned handle_client(void * arg)
{
    SOCKET fd = *(SOCKET*)arg;

    if(0 == fd)
    {
        std::cout << "the fd error" << std::endl;
        return 0;
    }

    WaitForSingleObject(g_SerMutex, INFINITE);
    g_clients[g_clientCnt++] = fd;
    ReleaseMutex(g_SerMutex);

    char buf[STRLEN_MAX] = {0};
    int bytes = 0;
    while((bytes = recv(fd, buf, STRLEN_MAX, 0)) != 0)
    {
        printf("recv data from client = %s\n", buf);
        sendMsg(buf, bytes);

    }

    WaitForSingleObject(g_SerMutex, INFINITE);

    for(int i = 0; i < g_clientCnt; i++)
    {
        if(g_clients[i] == fd)
        {
            while(i+1 < g_clientCnt)
            {
                g_clients[i] = g_clients[i+1];
                ++i;
            }
            break;
        }
    }
    g_clientCnt--;
    ReleaseMutex(g_SerMutex);
    closesocket(fd);
    return 0;
}

void sendMsg(char msgs[], int bytes)
{
    WaitForSingleObject(g_SerMutex, INFINITE);
    for(int i = 0; i < g_clientCnt; i++)
    {
        send(g_clients[i], msgs, bytes, 0);
    }
    ReleaseMutex(g_SerMutex);

}

void __main_server()
{
    WSADATA DATA;
    WSAStartup(MAKEWORD(2 ,2), &DATA);

    g_SerMutex = CreateMutexA(nullptr, false, nullptr);
    SOCKET serfd = socket(AF_INET, SOCK_STREAM, 0);
    if(0 == serfd)
    {
        std::cerr << "create serfd error" << std::endl;
        return;
    }

    int opt = 1;
    setsockopt(serfd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof opt);

    sockaddr_in bind_addr;
    bind_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_port = htons(8888);

    bind(serfd, (sockaddr*)&bind_addr, sizeof bind_addr);
    listen(serfd, SOMAXCONN);

    printf("server start to listen~~\n");
    while(true)
    {
        sockaddr_in client_addr;
        int len = sizeof client_addr;

        SOCKET fd = accept(serfd, (sockaddr*)&client_addr, &len);
        if(-1 == fd)
        {
            std::cerr << "accpet error" << std::endl;
            break;
        }

//        WaitForSingleObject(g_SerMutex,INFINITE);
//        g_clients[g_clientCnt++] = fd;
//        ReleaseMutex(g_SerMutex);

        HANDLE t1 = (HANDLE)_beginthreadex(nullptr, 0, handle_client, (void*)&fd, 0, nullptr);

        printf("client connect~~\tIP = %s, Port = %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    }
    closesocket(serfd);
    CloseHandle(g_SerMutex);
    WSACleanup();
}