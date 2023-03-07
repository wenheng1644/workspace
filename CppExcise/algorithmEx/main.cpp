//
// Created by wenheng on 22-10-26.
//

#include "algorithm"
#include "iostream"
#include "vector"
#include "iterator"
#include "random"
#include "boost/format.hpp"

void test_al1()
{
    std::vector<int> vals{2,1,3,4,222,32,56,0};
    auto min_pos = std::min_element(vals.begin(), vals.end());
    auto max_pos = std::max_element(vals.begin(), vals.end());
    std::cout << boost::format("min value = %d and max value = %d") % *min_pos % *max_pos << std::endl;

    auto ans = std::minmax({1,2,3,4,5});
    std::cout << boost::format("min = %d and max = %d") % ans.first % ans.second << std::endl;

    auto pos1 = std::find_if(vals.begin(), vals.end(), [](int v) {
        if(v > 3)
            return true;
        else
            return false;
    });

    std::cout << "pos1 = " << *pos1 << std::endl;

    std::vector<int> vals2{2,2,3};
    std::vector<int> vals3;
    if(vals == vals3)
    {
        std::cout << "yes" << std::endl;
    }
    else
    {
        std::cout << "no" << std::endl;
    }


    std::copy(vals.begin(), vals.end(), std::back_inserter(vals3));

    for(auto& v : vals3)
        std::cout << v << " ";
    std::cout << std::endl;
    std::vector<int> vals4;
    std::reverse_copy(vals.begin(), vals.end(), std::back_inserter(vals4));
    for(auto& v : vals4)
        std::cout << v << " ";

    auto cnt =  std::count_if(vals.begin(), vals.end(), [](int v){
        if(v == 3)
            return true;
        return false;
    });
    std::cout << "cnt = " << cnt << std::endl;

    auto pos = std::find_end(vals.begin(), vals.end(), vals3.begin(), vals3.end());
    if(pos != vals.end())
        std::cout << boost::format("pos's val = %d") % *pos << std::endl;

    auto firstBigPos = std::find_first_of(vals.begin(), vals.end(), vals2.begin(), vals2.end(), [](int v1, int v2){
        std::cout << boost::format("v1 = %d, v2 = %d") % v1 % v2 << std::endl;
        if(v1 >= v2)
        {
            return true;
        }
        return false;
    });

    if(firstBigPos != vals.end())
        std::cout << boost::format("*pos = %d and distance = %d") % *firstBigPos % (std::distance(vals.begin(), firstBigPos)+1) << std::endl;

    std::vector<int> vals5 = vals;
    vals5.push_back(13);

    auto pairs = std::mismatch(vals.begin(), vals.end(), vals5.begin());
    if(pairs.first == vals.end())
    {
        std::cout << "before is equal" << std::endl;
        if(pairs.second != vals5.end())
            std::cout << "vals end element is " << *pairs.second << std::endl;
    }

    auto l = [](int v){
        if(v >= 0)
            return true;
        return false;
    };

    if(std::none_of(vals.begin(), vals.end(), l))
        std::cout << "all great than 0" << std::endl;

}

void test_modiftyAl()
{
    std::vector<int> vals{1,2,3,4,5,6,7,8,9};

    auto iter = std::copy_backward(vals.begin(), vals.begin() + 3, vals.begin() + 5);
    for(const auto& v : vals)
        std::cout << v << " ";
    std::cout << boost::format("value = %d and distance = %d") % *iter % (std::distance(vals.begin(), iter) + 1)<< std::endl;

    std::vector<int> dest;

    std::transform(vals.begin(), vals.end(), vals.begin(), [](int v){
        return v * 10;
    });

    std::cout << std::endl;
    for(auto v : vals)
        std::cout << v << " ";


    std::vector<int> vals3;

    std::generate_n(std::back_inserter(vals3), 10, [](){
        std::default_random_engine engine(time(nullptr));
        std::uniform_int_distribution<int> distribution(0, 100);
        return distribution(engine);
    });
    std::cout << std::endl;
    for(auto& v : vals3)
        std::cout << v << " ";
}

void test_remove()
{
    std::vector<int> vals{1, 2, 5,3 ,77,12};
    auto pos = std::remove(vals.begin(), vals.end(), 3);
    vals.erase(pos, vals.end());
    if(pos == vals.end())
        std::cout << boost::format("is end") << std::endl;
    else
        std::cout << boost::format("*pos = %d size = %d distance = %d") % *pos % vals.size() % (std::distance(vals.begin(), pos) +1) << std::endl;

    std::cout << "test = " << std::distance(vals.begin(), vals.begin()) << std::endl;

    for(auto v : vals)
        std::cout << v << " ";

    std::vector<int> rmVals{1,2,3,3,45,4,3,2,1,3,2};
    std::cout << std::endl;
    std::cout << "orgin vals = ";
    for(const auto& v : rmVals)
        std::cout << v << " ";

    auto rmPos = std::unique(rmVals.begin(), rmVals.end(), [](int a, int b){ return a == b;});

    std::cout << std::endl;
    std::cout << "after vals = ";
    for(const auto& v : rmVals)
        std::cout << v << " ";

    std::vector<int> rotateV{1,2,3,4,5,6,7,8,9};
    auto roPos = std::rotate(rotateV.begin(), rotateV.begin() + 3, rotateV.end());
    std::cout << "\nrotate: ";
    for(auto& v : rotateV)
        std::cout << v << " ";

    std::cout << boost::format("*roPos = %d, distance = %d") % *roPos % std::distance(rotateV.begin(), roPos) << std::endl;
}

void test_premuation()
{
    std::vector<int> v{3,2,5,1,0,8};
    auto lam = [](int a) {
        std::cout << a << " ";
    };
    int cnt{};
    while(std::prev_permutation(v.begin(), v.end()))
    {
        std::for_each(v.begin(), v.end(), lam);
        std::cout << std::endl;
        ++cnt;
    }
//    std::next_permutation(v.begin(), v.end());
    std::for_each(v.begin(), v.end(), lam);
    std::cout << std::endl << "cnt = " << cnt << std::endl;
}

void test_partion()
{
    std::vector<int> v{2,3,41,1,36,74,233};

//    auto pos = std::partition(v.begin(), v.end(), [](int a) {
//        if(a > 10)
//            return true;
//        return false;
//    });
//    std::cout << boost::format("*pos = %d, distance = %d") % *pos % std::distance(v.begin(), pos) << std::endl;
//    for(auto& n : v)
//        std::cout << n << " ";

    std::vector<int> cp1, cp2;
    std::partition_copy(v.begin(), v.end(), std::back_inserter(cp1), std::back_inserter(cp2), [](int a){
        if(a > 10)
            return true;
        return false;
    });

    auto lam = [](int v, int cnt){
        char c = cnt == 0 ? '\n' : ' ';
        std::cout << v << c;
    };

    int cnt, cnt2;
    cnt = cnt2 = v.size();
    auto f = std::bind(lam, std::placeholders::_1, cnt--);
    std::for_each(cp1.begin(), cp1.end(), f);

}

void test_search()
{
    std::vector<int> v{12,23,4,66,233,44};
    std::sort(v.begin(), v.end());
    if(std::binary_search(v.begin(), v.end(), 4, std::less<int>()))
        std::cout << "find it" << std::endl;

    for(auto n : v)
        std::cout << n << " ";
}

void test_include()
{
    std::vector<int> vals{1,2,3,4,5,6,7};
    std::vector<int> vals2{3,5,7};

    if(std::includes(vals.begin(), vals.end(), vals2.begin(), vals2.end()))
        std::cout << "include it" << std::endl;
}

int main()
{
    test_include();
    return 0;
}