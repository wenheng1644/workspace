#include <iostream>
#include <string>
#include "boost/version.hpp"

#include "boost/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/asio/thread_pool.hpp"
#include "boost/asio.hpp"

#include "boost/smart_ptr.hpp"
#include "boost/make_shared.hpp"

#include "boost/pool/pool.hpp"
#include "boost/pool/singleton_pool.hpp"
#include "boost/pool/pool_alloc.hpp"

void hello()
{
    std::cout << "hello my girl" << std::endl;
}

void smart_ptr1()
{
    boost::scoped_ptr<std::string> p1(new std::string("text"));
    std::cout << "*p1: " << *p1 << std::endl;
    std::cout << "bytes: " << p1->size() << std::endl;
}

void smart_ptr2()
{
    boost::scoped_array<int> sa(new int[10]);
    std::fill_n(sa.get(), 10, 5);

    for(int i = 0; i < 10; i++)
        std::cout << sa[i] << std::endl;
}

void smart_ptr3()
{
    boost::shared_ptr<int> p(new int(1));
    assert(p.unique());

    auto p2 = p;
    std::cout << "当前计数: " << p2.use_count() << std::endl;

    *p2 = 520;

    std::cout << "输出p： " << *p << std::endl;

    assert(p == p2);
}

void smart_ptr4()
{
    boost::shared_ptr<int> p = boost::make_shared<int>(1);
    std::cout << "cnt: " << p.use_count() << std::endl;

    boost::weak_ptr<int> wk(p);
    if(p)
    {
        boost::shared_ptr<int> p2 = wk.lock();
        *p2 = 100;

        std::cout << *p << std::endl;
        std::cout << "cnt: " << wk.use_count() << std::endl;
    }

    std::cout << "now the cnt: " << wk.use_count() << std::endl;

    wk.reset();

    std::cout << "last cnt: " << wk.use_count();
}

void memory_pool1()
{
    boost::pool<> p(10);
    int* p1 = (int*)p.malloc();
    *p1 = 100;

    std::cout << *p1 << std::endl;

    if(p.is_from(p1))
        std::cout << "yes, p1 from the p pool" << std::endl;

    std::cout << p.get_requested_size() << std::endl;

    std::cout << p.get_max_size() << std::endl << std::endl;
    p.free(p1);

    for(int i = 0; i < 10; i++)
        p.ordered_malloc(10);

    std::cout << "now the memory bytes: " << p.get_requested_size() << std::endl;
}

struct tag {};

typedef boost::singleton_pool<tag, sizeof (int)> spl;
void memory_pool2()
{
    int* p = (int *)spl::malloc();

    *p = 100;

    std::cout << *p << std::endl;

    spl::release_memory();
}

struct student
{
    char        name[10];
    uint        id;
    char        sex;
    char        age;
};

void memory_pool_macll()
{
    std::vector<student* , boost::fast_pool_allocator<student*>> v(10);

    student* p1 = new student;

    v[1] = p1;

    boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(student*)>::release_memory();
}

boost::mutex m;
struct count
{
    count(int id) : m_id(id) {}
    void operator()()
    {
        for(int i = 0; i < 5; i++)
        {
            boost::lock_guard<boost::mutex> lock(m);
            std::cout << "id: " << m_id << "\tvalue: " << i << std::endl;
        }
    }



    int m_id;
};

void thread1()
{
//    boost::thread t1(count(1));
//    boost::thread t2(count(2));
//
//    t1.join();
//    t2.join();

    std::cout << memory_pool1 << std::endl;
    std::cout << &memory_pool1 << std::endl;
    std::cout << "==============================";
}

void cor_thread1()
{
    for(int i = 0;i < 10; i++)
    {
        boost::lock_guard<boost::mutex> gurad(m);
        std::cout << "cor_thread1-->\tthreadId: " << boost::this_thread::get_id() << "\tvalue: " << i << std::endl;
    }

}

void cor_thread2()
{
    for(int i = 0;i < 10; i++)
    {
        boost::lock_guard<boost::mutex> gurad(m);
        std::cout << "cor_thread2-->\tthreadId: " << boost::this_thread::get_id() << "\tvalue: " << i << std::endl;
    }

}

boost::condition_variable_any g_cd;
bool g_condtion = false;
void varconr_thread()
{
    boost::lock_guard<boost::mutex> gurad(m);

    while(!g_condtion)
    {
        printf("thread is coming sleep\n");
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        printf("thread sleep done\n");
        g_cd.wait(m);
        printf("thread wait done\n");
    }

    printf("thread is done\n");
}

void my_task()
{
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    boost::lock_guard<boost::mutex> gl(m);
    std::cout.flush();
    std::cout << "my task~\ttheadID: " << boost::this_thread::get_id() << std::endl;
    std::cout.flush();
}

int main() {

//    boost::thread t(&hello);
//    t.join();
//    thread1();

//    boost::thread t1(cor_thread1);
//    boost::thread t2(cor_thread2);
//
//    t1.join();
//    t2.join();

//    boost::thread t1(&varconr_thread);
//    t1.detach();
//    boost::this_thread::sleep(boost::posix_time::millisec(100));
//
//    printf("on here\n");
//    m.lock();
//    g_condtion = true;
//    m.unlock();
//
//    g_cd.notify_one();
//
//    printf("main thread here\n");
//
//    getchar();

    boost::asio::thread_pool tp(4);

    for(int i = 0;i < 20; i++)
    {
        boost::asio::post(&my_task);
    }

    tp.join();
    return 0;
}
