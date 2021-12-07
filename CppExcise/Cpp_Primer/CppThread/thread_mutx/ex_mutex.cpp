#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> vc{1,2,3};
mutex g_mutex;

void add_to_vec(int val)
{
    lock_guard<mutex> guard(g_mutex);
    vc.push_back(val);
    cout << "add a val: " << val << endl;    
}

bool find_val(int val)
{
    lock_guard<mutex> guard(g_mutex);

    bool isFind = false;
    while(!isFind)
    {
        isFind = find(begin(vc),end(vc),val) != end(vc);
    }

    cout << "find it !!!!!!!!" << endl;

    return isFind;
}

int main()
{
    cout << "begining...." << endl;
    thread t1(add_to_vec,5);
    thread t2(find_val,5);

    t1.detach();
    t2.detach();

    return 0;
}