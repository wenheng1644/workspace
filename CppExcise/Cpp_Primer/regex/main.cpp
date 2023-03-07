//
// Created by wenheng on 22-10-22.
//
#include "regex"
#include "iostream"
#include <string>

void test_rex1()
{
    std::regex reg(R"(<(.*)>.*</.*>)");
    std::string s("<tag>w</tag2>");

    bool ans = std::regex_match(s, reg);
    std::cout << ans << std::endl;
}

void test_smatch()
{
    std::string str("<hey>what the fuck<aaa></hey>\n<aaa>shit</aaa>");
    std::smatch m;
//    bool ans = std::regex_search(str, m, std::regex("<(.*)>(.*)</\\1>"));
//    if(ans)
//    {
//        std::cout << "yes" << std::endl;
//        std::cout << "m.str(): " << m.str(1) << std::endl;
//        std::cout << "m.length(): " << m.length() << std::endl;
//        std::cout << m[0];
//    }

    auto pos = str.cbegin();
    auto end = str.cend();
    for(; std::regex_search(pos, end, m, std::regex("<(.*)>(.*)</\\1>")); pos = m.suffix().first)
    {
        std::cout << "m[0]: " << m[0] << std::endl;
        std::cout << "m[1]: " << m[1] << std::endl;
        std::cout << "m.length(): " << m.length() << std::endl;
        std::cout << "m.position(0): " << m.position(0) << std::endl;
        std::cout << "\n" << std::string(10, '-') << std::endl;
    }

    std::regex reg("<(.*)>(.*)</\\1>");
    std::sregex_iterator iter(str.cbegin(), str.cend(), reg);
    std::sregex_iterator iter_end;

    while(iter != iter_end)
    {
        std::cout << "" << iter->str(0) << std::endl;
        iter++;
    }


}

int main()
{
    test_smatch();
    return 0;
}