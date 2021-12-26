#include <iostream>
#include <regex>

using namespace std;

void testRe()
{
    regex r("[^0-9][[:alnum:]]+\\.(cpp|c{1,2})");
    smatch reslut;
    cout << "enter you filename:";
    string filename;
    while(cin >> filename)
    {
        if(regex_search(filename,reslut,r)) {
            cout << "match reslut: " << reslut.str() << endl;
            cout << "change the reslut: " << reslut.format("CHANGE.$1",regex_constants::format_default);
        }
        else
            cout << "the filename can't match: " << filename << endl;
    }

}

//遍历字符串中所有符合模式的子串
void iter_Re()
{
    string file = "hello world,how are you doing?";
    string partten = "[[:alpha:]]+";
//s
    regex r(partten,regex::icase);

    int index{};
    for(sregex_iterator it(begin(file),end(file),r),end_iter; it != end_iter;++it)
    {
        cout << ++index  << ": "<< it->str() << endl;
        cout << "it->prefix(): " << it->prefix() << endl;
        cout << "it->suffix(): " << it->suffix() << endl;
    }

}

void testExRe()
{
    string parretn = "(^[[:digit:]]{5}$|[[:digit:]]{5}-[[:digit:]]*)";
    regex r(parretn);

    string res;

    while(cin >> res && res != "q")
    {
        smatch match;
        regex_search(res,match,r);

        if(match.size() == 0)
            cout << "match is failure..." << endl;
        else
            cout << "mtach is sccessful: " << match.str() << endl;
    }

}

int main() {
//    testRe();
//    cout << "the second: " << endl;
//    string str1 = "I love you {520}";
//    regex r("[[:digit:]]+");
//    cout << "res: " << regex_replace(str1,r,"1314");
//    iter_Re();

    testExRe();
    return 0;
}
