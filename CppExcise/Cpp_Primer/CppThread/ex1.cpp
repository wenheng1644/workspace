#include <iostream>
#include <thread>
#include <string>
using namespace std;

void thread1()
{
    cout << "thread1 running~~~\n";
    cout << "(inside)thread1'stid: " << this_thread::get_id() << endl;
}

void thread2()
{
    cout << "thread2 running~~~\n";
}

void processData(string& str)
{
    cout << "The Old string is " << str << endl;

    str = "Sherlock Homes is my idot!!!";

    cout << "The Change str is " << str << endl;
}

thread f()
{
    thread t1(thread1);

    return t1;
}

int main()
{
    cout << "main thread's tid: " << this_thread::get_id() << endl;
    thread noThead;
    cout << "no thread's tid: " << noThead.get_id() << endl;
    thread t1(thread1);
    cout << "(outside)thread1's tid: " << t1.get_id() << endl;
    t1.detach();    

    thread t2(thread2);
    t2.detach();

    string str = "Hello";

    thread t3(processData,std::ref(str));
    t3.join();

    cout << "The str: " << str << endl;

    // thread test = std::move(f());
    // test.join();
    return 0;    
}