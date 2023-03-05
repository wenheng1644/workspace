//
// Created by нд╨Ц on 2022/1/29.
//

#include <cstdlib>
#include <iostream>
#include <exception>
#include "typeinfo"
#include "dram_test.h"
using namespace std;
//
//void* operator new(size_t bytes)
//{
//    void* ptr = malloc(bytes);
//
//    if(ptr)
//    {
//        cout << "malloc: " << bytes << "bytes\t" << "address: " << ptr;
//        return ptr;
//    }
//    else
//        throw bad_alloc();
//}
//
//void operator delete(void* ptr) noexcept
//{
//    cout << ">>>>>>>>>>>>>free";
//    free(ptr);
//}

void test_typeinfo()
{
    int a[10] = {};
    A* ptr1 = new A;
    cout << typeid(std::string).name() << endl;
    cout << typeid(a).name() << endl;
    cout << typeid(ptr1).name() << endl;
    cout << typeid(*ptr1).name() << endl;
}

int main()
{
//    int* ptr = new int(0);
//
//    delete ptr;

//    void * ptr = malloc(sizeof (int));
//    int*val = new(ptr) int(12);
//
//    cout << "val: " << *val << endl;
//    cout << "address ptr: " << ptr << "\taddress val: " << val << endl;

//    A* pa = new C;
//    if(B* pb = dynamic_cast<B*> (pa))
//        cout << "1: true";
//    else
//        cout << "1: false";
//
//    cout << endl;
//    B* pb1 = new B;
//    if(C* pc1 = dynamic_cast<C*> (pb1))
//        cout << "2: true" << endl;
//    else
//        cout << "2: false" << endl;
//
//    if(typeid(*pa) == typeid(A))
//        cout << "yes" << endl;
//    else
//        cout << "no" << endl;
//
//    cout << typeid(*pa).name() << endl;
//    A* pa2 = new D;
//    if(B* pb2 = dynamic_cast<B*> (pa2))
//        cout << "3: true";
//    else
//        cout << "3: false";

    test_typeinfo();
    return 0;
}