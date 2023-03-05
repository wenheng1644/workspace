//
// Created by нд╨Ц on 2022/10/3.
//
#include "win_client_chat.h"
#include "fcntl.h"
#include "unistd.h"

static bool g_isDisconnect = false;
static HANDLE g_mutex;

unsigned handle_puts(void * args)
{
    SOCKET fd = *(SOCKET*)args;
    const int STRLEN_MAX = 30;

    while(true)
    {
        char buf[STRLEN_MAX] = {0};
        fgets(buf, STRLEN_MAX, stdin);

        int len = strlen(buf);
        if(len == 0)
        {
            printf("puts str is empty...\n");
            continue;
        }
        if(strcmp(buf, "q\n") == 0)
        {
            printf("quit~~\n");
            break;
        }

        int total = 0;
        while(true)
        {
            char temp[STRLEN_MAX] = {0};
//            if(recv(fd, temp, STRLEN_MAX, 0) == 0)
//                break;

            WaitForSingleObject(g_mutex, INFINITE);
            if(g_isDisconnect)
                break;
            ReleaseMutex(g_mutex);


            int bytes = send(fd, buf + total, len - total, 0);
            if(0 == bytes || -1 == bytes)
                break;

            total += bytes;
        }
    }

//    closesocket(fd);
    return 0;
}

unsigned handle_read(void * args)
{
    SOCKET fd = *(SOCKET*)args;

    const int STRLEN_MAX = 30;

    while(true)
    {
        char buf[STRLEN_MAX] = {0};
        int bytes = recv(fd, buf, STRLEN_MAX, 0);

        if(0 == bytes)
            break;

        if(-1 == bytes)
        {
            int err = WSAGetLastError();
            if(WSAEWOULDBLOCK == err || WSAETIMEDOUT)
                continue;
            break;
            printf("current err = %d\n", err);
        }

        printf("recv data = %s\n", buf);
    }
    WaitForSingleObject(g_mutex, INFINITE);
    g_isDisconnect = true;
    ReleaseMutex(g_mutex);
}

void __main_client()
{
    WSADATA DATA;
    WSAStartup(MAKEWORD(2,2), &DATA);

    CreateMutexA(nullptr, false, nullptr);

    SOCKET fd = socket(AF_INET, SOCK_STREAM, 0);
    if(SOCKET_ERROR == fd)
    {
        std::cerr << "fd create error" << std::endl;
        WSACleanup();
        return;
    }

    sockaddr_in addr;
    addr.sin_port = htons(8888);
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;

    if(connect(fd, (sockaddr*)&addr, sizeof addr) == -1)
    {
        std::cerr << "connect error" << std::endl;
        WSACleanup();
        return;
    }

    u_long opt = 1;
    if(ioctlsocket(fd, FIONBIO, &opt) == -1)
    {
        printf("set io opt error\n");
        WSACleanup();
        return;
    }

    printf("connect successfully\n");

    HANDLE hPuts, hRead;
    hPuts = (HANDLE)_beginthreadex(nullptr, 0, handle_puts, (void*)&fd, 0, nullptr);
    hRead = (HANDLE)_beginthreadex(nullptr, 0, handle_read, (void*)&fd, 0, nullptr);

    WaitForSingleObject(hRead, INFINITE);
    WaitForSingleObject(hPuts, INFINITE);

    printf("done...\n");
    closesocket(fd);
    CloseHandle(g_mutex);
    WSACleanup();
}