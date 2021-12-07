#include "temFunc.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

void Ex1()
{
    int v1 = 1;
    int v2 = 3;

    cout << "比较int类型： " << "v1: " << v1 << " v2: " << v2 << endl;
    cout << "结果码: " << compare(v1,v2) << endl;

    string str1 = "hello";
    string str2 = "Hello";

    cout << "比较string类型: " << "str1: " << str1 << "\tstr2: " << str2 << endl;
    cout << "结果码: " << compare(str1,str2) << endl;
}

void Ex2()
{
    vector<int> vc{3,5,9,2,1,15,0};
    list<string> l{"hello","My","lover","yeyi"};

    auto ans1 = find_temp(vc.begin(),vc.end(),100);
    auto ans2 = find_temp(l.begin(),l.end(),"lover");

    if(ans1 != vc.end())
        cout << "vector has the val: " << *ans1 << endl;
    else
        cout << "vector has not the val..." << endl;

    if(ans2 != l.end())
        cout << "list has the val: " << *ans2 << endl;
    else
        cout << "list has not the val: " << endl;
    
}

void Ex3()
{
    vector<int> vc{1,2,3,5,6,8,78,99};

    print_temp(vc);
}

template <typename T>
void temp_print(T& conter)
{
    for(auto iter = begin(conter); iter != end(conter); iter++)
    {
        cout << *iter << " ";
    } 
    cout << endl;
}

int main(int argc,char* argv[])
{

    // Ex3();
    vector<int> vc{1,2,3,4,5,6,7};
    temp_print(vc);
    return 0;
}