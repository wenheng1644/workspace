//
// Created by нд╨Ц on 2022/7/6.
//
#include <iostream>
#include <cstring>
#include <vector>
#include <forward_list>
#include "winsock2.h"
#include "windows.h"
#include "process.h"

#include "myWinSock.h"
#include "excise1.h"

#include "win_ChatExcise.h"
void getData()
{
//    int quantity, price;
//    char department[20] = {0};
//
//    printf("please enter your data for quantity,price and department~\n");
//    int nums = scanf_s("%d %d %s",&quantity, &price, department);
//    printf("\nnums:%d\tquantity:%d\tprice:%d\tdepartment:%s\n", nums,quantity, price, department);

    char test[20] = {0};
    char *p = nullptr;
    while( (p = gets(test)) != nullptr)
    {
        printf("test:%s\ttest:%x\t&test:%x\t&p:%x\n", test, test, &test, p);
    }


}

void getMaxLine()
{
    const int MAXLINE = 1000;
    char input[MAXLINE] = {0};
    char answer[MAXLINE] = {0};

    int maxLen = 0;
    while(fgets(input, MAXLINE, stdin) != nullptr && input[0] != '\n')
    {
        input[strlen(input) - 1] = '\0';
        if(strlen(input) > maxLen)
        {
            maxLen = strlen(input);
//            memset(answer, 0, MAXLINE);
//            input[maxLen-1] = '\0';
            strncpy(answer, input, maxLen);
        }
        printf("input: %s\tlen: %d\tcurrent max line: %s\n", input, strlen(input), answer);
    }
}

//void testExicse1()
//{
//    int colums[MAXCOL] = {0};
//    char input[MAXCOL] = {0};
//    char output[MAXCOL] = {0};
//
//    int cnt = read_colums(colums, MAXCOL);
//
//    if(cnt <= 0)
//    {
//        perror("the numbers is worrng...");
//        return;
//    }
//
//
//    while(fgets(input, MAXCOL, stdin) != nullptr && input[0] != '\n')
//    {
//        printf("the org string: %s\n", input);
//        rerange(output, input, colums, cnt);
//        printf("the fix string: %s\n", output);
//    }
//
//    printf("program done.");
//
//    exit(EXIT_SUCCESS);
//
//}

void WSA_test()
{
    sockaddr_in addr;
    char* info = "127.0.0.1:8888";
    int size = sizeof addr;

    WSADATA data;
    WSAStartup(MAKEWORD(2,2), &data);
    WSAStringToAddress(info, AF_INET, 0,(sockaddr *)&addr, &size);

    printf("ip: %s\tport: %d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

    WSACleanup();
}

void test_class()
{
    base* p_d = new drive_public(1,2,3);
    p_d->print_it();
}

void test_vector()
{
    std::vector<int> v{1,2,3,4,5};

    std::cout << "sizeof(vector) = " << sizeof(std::vector<int>) << "\tsizeof(v) = " << sizeof v << std::endl;
    std::cout << "max_size = " << v.max_size() << "\tcapcaity = " << v.capacity() << std::endl;

}

bool checkValue(std::vector<int>::const_iterator iter1, std::vector<int>::const_iterator iter2, int value)
{
    while(iter1 != iter2)
    {
        if(*iter1 == value)
            return true;
        iter1++;
    }
    return false;
}

void test_forwardlist()
{
    std::forward_list<int> forwardList{1,2,3,4};

    auto iter = forwardList.before_begin();

    for(int i = 0;i < 5; i++)
    {
        iter = forwardList.insert_after(iter, 222 + i);
    }

    for(auto& v : forwardList)
        std::cout << v << " ";
}

void insert_to_forwardlist(std::forward_list<std::string>& flist, const std::string& tag, const std::string& str)
{
    auto iter = flist.begin();

    auto end_iter = flist.begin();
    while(true)
    {
        if(*iter == tag)
        {
            flist.insert_after(iter, str);
            return;
        }
        end_iter = iter;
        iter++;
        if(iter == flist.end())
            break;
    }

    flist.insert_after(end_iter, str);
}

void test_resize()
{
    std::vector<int> vc{1,2,3,4,5,6};

    std::cout << "size = " << vc.size() << std::endl;
    vc.resize(2);
    std::cout << "resize(2) = " << vc.size() << std::endl;

    vc.resize(10,111);

    int i = 1;
    for(auto& v : vc)
        std::cout << "[ " << i++ << " ]: " << v << " ";
}

unsigned WINAPI thread_main(void * arg)
{
    int cnt = *(int*)arg;

    for(int i = 0; i < cnt; i++)
    {
        std::cout << "times: " << i+1 << "\thello world" << std::endl;
        Sleep(3000);
    }
    return 0;
}

void test_winthread()
{
    HANDLE hThread;
    unsigned threadId;
    int param = 5;

    hThread = (HANDLE)_beginthreadex(nullptr, 0, thread_main, (void*)&param, 0, &threadId);
    if(0 == hThread)
    {
        std::cerr << "create thread error" << std::endl;
        return;
    }

//    Sleep(10000);
    DWORD res;
    if((res = WaitForSingleObject(hThread, 3000)) == WAIT_FAILED)
    {
        std::cerr << "wait error" << std::endl;
        return;
    }


    std::cout << "main thread return\tres = " << (res == WAIT_OBJECT_0 ? "signaled" : "time-out") << std::endl;
}

CRITICAL_SECTION g_cs;
HANDLE g_mutex;
int g_num = 0;
unsigned add_thread(void * param)
{
    int cnt = *(int*)param;
//    EnterCriticalSection(&g_cs);
    WaitForSingleObject(g_mutex, INFINITE);
    for(int i = 0; i < cnt; i++)
    {
        std::cout << "cnt = " << i+1 << "\tadd thread" << std::endl;
        g_num += i;
    }
//    LeaveCriticalSection(&g_cs);
    ReleaseMutex(g_mutex);
    return 0;
}

unsigned del_thread(void * param)
{
    int cnt = *(int*)param;
//    EnterCriticalSection(&g_cs);
    WaitForSingleObject(g_mutex, INFINITE);
    for(int i = 0; i < cnt; i++)
    {
        std::cout << "cnt = " << i+1 << "\tdel thread" << std::endl;
        g_num -= i;
    }
//    LeaveCriticalSection(&g_cs);
    ReleaseMutex(g_mutex);
    return 0;
}

void test_criSection()
{
//    InitializeCriticalSection(&g_cs);
    g_mutex = CreateMutexA(nullptr, false, nullptr);
    std::cout << "the init value = " << g_num << std::endl;
    HANDLE arr[20];
    int param = 5;
    for(int i = 0;i < 20; i++)
    {
        unsigned threadId;
        if(i % 2 == 0)
            arr[i] = (HANDLE)_beginthreadex(nullptr, 0, add_thread, (void*)&param, 0, &threadId);
        else
            arr[i] = (HANDLE)_beginthreadex(nullptr, 0, del_thread, (void*)&param, 0, &threadId);

//        std::cout << "thread id = " << threadId << std::endl;
    }


    WaitForMultipleObjects(20, arr, true, INFINITE);
//    DeleteCriticalSection(&g_cs);
    CloseHandle(g_mutex);
    std::cout << "the last value = " << g_num << std::endl;
}

HANDLE semRead,semAcc;
int g_sum = 0;

unsigned handle_read(void * arg)
{
    for(int i = 0; i < 5; i++)
    {
        fputs("value =", stdout);
        WaitForSingleObject(semRead, INFINITE);
//        fgets((char*)&g_sum, sizeof(g_sum),stdin);
        scanf("%d", &g_sum);
//        printf("g_sum = %d", g_sum);
        ReleaseSemaphore(semAcc, 1, nullptr);
    }
    return 0;
}

unsigned handle_Acc(void * arg)
{
    int sum = 0;
    for(int i = 0; i < 5; i++)
    {
        WaitForSingleObject(semAcc, INFINITE);
        sum += g_sum;
        ReleaseSemaphore(semRead, 1, nullptr);
    }
    std::cout << "sum = " << sum << std::endl;
    return 0;
}

void test_sem()
{
    semRead = CreateSemaphoreA(nullptr, 1, 1, nullptr);
    semAcc = CreateSemaphoreA(nullptr, 0, 1, nullptr);

    HANDLE t1,t2;
    t1 = (HANDLE)_beginthreadex(nullptr, 0, handle_read, nullptr, 0, nullptr);
    t2 = (HANDLE)_beginthreadex(nullptr, 0, handle_Acc, nullptr, 0, nullptr);

    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);

    CloseHandle(semAcc);
    CloseHandle(semRead);
}

const int g_strlen = 20;
static char g_strs[g_strlen];
HANDLE gHevent;

unsigned accNumOfA(void* arg)
{
    int cnt = 0;
    WaitForSingleObject(gHevent, INFINITE);
    for(int i = 0; g_strs[i] != '\0'; i++)
    {
        if(g_strs[i] == 'A')
            cnt++;
    }

    printf("Num of A = %d\n", cnt);
    return 0;
}

unsigned accNumOfOther(void* arg)
{
    int cnt = 0;
    WaitForSingleObject(gHevent, INFINITE);
    char* ptr = g_strs;

    while(*ptr != '\0')
    {
        if(*ptr != 'A')
            cnt++;

        ++ptr;
    }
    printf("Num of Other = %d\n", cnt);
    return 0;
}

void test_event()
{
    HANDLE t1, t2;
    gHevent = CreateEventA(nullptr, true, false, nullptr);
    t1 = (HANDLE)_beginthreadex(nullptr, 0, accNumOfA, nullptr, 0, nullptr);
    t2 = (HANDLE)_beginthreadex(nullptr, 0, accNumOfOther, nullptr, 0, nullptr);

    std::cout << "get your number =";
    fgets(g_strs, g_strlen, stdin);
    SetEvent(gHevent);

    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);

    std::cout << "done " << std::endl;
    ResetEvent(gHevent);
    CloseHandle(gHevent);
}

int main()
{
//    testExicse1();
//    WSA_test();
//    std::vector<int> v{2,3,5,7,0};
//    if(checkValue(v.cbegin(), v.cend(), 6))
//        std::cout << "find it" << std::endl;
//    else
//        std::cout << "no find it" << std::endl;

//    std::forward_list<std::string> l{"hello world", "guys", "fuck"};
//    insert_to_forwardlist(l, "guy", "ok?");



//
//    for(auto& v : l)
//        std::cout << v <<  " ";

//    myWinSock::gethostInfo();
    __main_server();
    return 0;
}
