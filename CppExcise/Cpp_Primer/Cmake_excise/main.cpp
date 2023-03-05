#include "iostream"
#include "thread"
#include "mutex"
#include "condition_variable"

bool g_flag = false;
std::mutex g_mutex;
std::condition_variable g_cv;

void prodiver()
{
    while(true)
    {
        {
            std::lock_guard<std::mutex> lg(g_mutex);
            g_flag = true;
            std::cout << "work it..." << "\tthread Id: " << std::this_thread::get_id() << std::endl;
        }
        g_cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer()
{
    while(true)
    {
        {
            std::unique_lock<std::mutex> ul(g_mutex);
            g_cv.wait(ul, [](){ return g_flag;});

            std::cout << "use it..." << "\tthread Id: " << std::this_thread::get_id() << std::endl;
            g_flag = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));


    }
}

int main()
{
    std::thread t1(&prodiver);
    std::thread t2(&consumer);

    t1.join();
    t2.join();

    return 0;
}