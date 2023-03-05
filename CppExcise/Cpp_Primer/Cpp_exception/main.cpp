//用于测试异常代码

#include <iostream>

using namespace std;

void test1() noexcept(true);

int main()
{
    int a = 0;

    while(cin >> a)
    {
        try{
            if(a == 0)
                throw runtime_error("can't be zero!!!");
            int b = 3 / a;
            cout << "b: " << b << endl;
        }
        catch (runtime_error err)
        {
            cout << err.what();
        }

    }

    return 0;

}

