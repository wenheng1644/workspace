//
// Created by нд╨Ц on 2022/4/23.
//

#include "thread"
#include "mutex"
#include "iostream"
#include "vector"
#include "chrono"
#include "random"
#include "exception"
#include "future"
#include "cstring"
#include "boost/format.hpp"

#include "task.h"
int g_num = 0;
std::mutex g_mutex;

void thread_run(int id)
{
    std::lock_guard<std::mutex> g_lock(g_mutex);
//    std::cout << "id: " << id << std::endl;
    boost::format fmt("id: %d\tg_num: %d");
    for(int i = 0;i < 3; i++)
    {
        g_num++;
        std::cout << fmt % id % g_num << std::endl;
    }

}

int dosomething(char c)
{
    std::default_random_engine dre(c);
    std::uniform_int_distribution<int> id(10,1000);

    for(int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
        std::cout.put(c).flush();
    }
    return c;
}

int func1()
{
    dosomething('.');
}

int func2()
{
    dosomething('+');
}

void test()
{
    std::cout << "func1 for background\nfunc2 for forground" << std::endl;

    std::future<int> res1(std::async(&func1));

    int res2 = func2();

    int res = res1.get() + res2;

    std::cout << "result of func1 + func2 = " << res << std::endl;
}

void do_promise(std::promise<std::string>& p)
{
    std::cout << "enter your charater...." << std::endl;
    char c = std::cin.get();

    std::cout << "your input: " << c << std::endl;

    p.set_value(std::string("read: ") + c);
}

void test_promise()
{
    std::promise<std::string> p;
    std::thread t(&do_promise, std::ref(p));
    t.detach();

    std::future<std::string> f(p.get_future());

    std::cout << "my get: " << f.get() << std::endl;
}

double compute(int x, int y)
{
    return x + y;
}

void test_taskpack()
{
    std::packaged_task<double(int, int)> task(&compute);

    std::future<double> f(task.get_future());

    task(1, 2);

    std::cout << f.get() << std::endl;
}

int main()
{
//    std::thread t1(&thread_run, 0);
//    std::thread t2(&thread_run, 1);
//
//    t2.join();
//    t1.join();

//    task task_obj;
//    std::thread product_t(&task::proudct_task, &task_obj);
//
//    std::vector<std::thread> threads(5);
//
//    for(int i = 0; i < 5; i++)
//    {
//        threads[i] = std::thread(&task::consume_task, &task_obj);
//    }
//
//    product_t.join();
//    for(int i = 0; i < 5; i++)
//        threads[i].join();
    std::cout << "hello world" << std::endl;
    test_taskpack();
    return 0;
}