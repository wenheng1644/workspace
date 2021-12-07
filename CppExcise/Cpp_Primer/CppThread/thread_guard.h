#ifndef THREAD_GUARD
#define THREAD_GUARD

#include <thread>
//使用RAII技术
class thread_guard
{
public:
    thread_guard(std::thread& pthread) : t(std::move(pthread)) {}

    ~thread_guard()
    {
        if(t.joinable())
            t.join();
    }

    //资源不允许拷贝
    thread_guard(thread_guard& t1) = delete;
    thread_guard& operator=(thread_guard& t1) = delete;

private:
    std::thread t;
};


#endif