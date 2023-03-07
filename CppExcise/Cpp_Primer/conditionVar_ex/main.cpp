//
// Created by wenheng on 22-10-21.
//


#include "iostream"
#include "condition_variable"
#include "mutex"
#include "thread"
#include "queue"

bool readFlag = false;
std::mutex g_mutex;
std::condition_variable g_readConVar;

void thread_prod()
{
    {
        std::lock_guard<std::mutex> lockGuard(g_mutex);
        readFlag = true;
    }
    std::cout << "start to notify all" << std::endl;
    g_readConVar.notify_all();
}

void thread_get()
{
    {
        std::unique_lock<std::mutex> uniqueLock(g_mutex);
        g_readConVar.wait(uniqueLock, [](){ return readFlag;});
        std::cout << "get it" << std::endl;
    }
}

std::queue<int> g_queue;

void product_t(int cnt)
{
    for(int i = 0; i < cnt; i++)
    {
        std::lock_guard<std::mutex> lockGuard(g_mutex);
        g_queue.push(i+1);
    }
    g_readConVar.notify_one();
}

void conmuser()
{
    while(true)
    {
        int val;
        {
            std::unique_lock<std::mutex> uniqueLock(g_mutex);
            g_readConVar.wait(uniqueLock, [](){ return !g_queue.empty();});
            val = g_queue.front();
            g_queue.pop();
        }
        std::cout << "val = " << val << std::endl;
    }
}



int main()
{
    std::thread t1(product_t, 6);
    std::thread t2(conmuser);

    t1.join();
    t2.join();

    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}

