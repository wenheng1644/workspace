#include <iostream>
#include <bitset>

using namespace std;
void ex_bitset()
{
    bitset<16> b("1100");
    cout << "print data: " << b << endl;
    auto res = b.to_ullong();
    cout << "to_ullong: " << res << endl; 
    cout << "b[0]: " << b[0] << endl;
    b[0] = 1;
    cout << "reset b[0]: " << b[0] << endl;
    cout << "the \'1\' have: " << b.count() << endl;  
    cout << "flip(): " << b.flip() << endl;
}

int main()
{
    ex_bitset();
    return 0;
}