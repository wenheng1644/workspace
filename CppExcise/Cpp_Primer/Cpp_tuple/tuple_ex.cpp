#include <tuple>
#include <iostream>
#include <algorithm>

using namespace std;

void tuple_ex()
{
    auto t = make_tuple(1,2,3);

    cout << "print the tuple data:" << endl;
    cout << "the tuple have: " << tuple_size<decltype(t)>::value << endl;
    cout << "t1: " << get<0>(t) << " t2: " << get<1>(t) << " t3: " << get<2>(t) << endl;
}


int main(void)
{
    tuple_ex();

    return 0;
}