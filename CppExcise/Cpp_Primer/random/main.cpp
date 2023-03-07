//
// Created by wenheng on 22-10-22.
//

#include "random"
#include "iostream"

#include <ctime>
void test_rand()
{
    std::default_random_engine eng(time(nullptr));
    std::uniform_int_distribution<int> di(0, 100);

    for(int i = 0; i < 10; i++)
    {
        std::cout << di(eng) << " ";
    }

}


int main()
{
    test_rand();
    return 0;
}