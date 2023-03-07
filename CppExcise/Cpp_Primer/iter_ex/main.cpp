//
// Created by wenheng on 22-10-23.
//

#include <iterator>
#include "iostream"
#include "vector"
#include "list"
#include "algorithm"
#include "boost/format.hpp"


void test_backInsert()
{
    std::vector<int> v;
    std::back_insert_iterator<std::vector<int>> iter(v);
    *iter = 1;
    ++iter;
    *iter = 2;
    ++iter;
    std::back_inserter(v) = 4;
    *iter = 3;

    v.reserve(v.size() * 2);
    std::copy(v.begin(), v.end(), std::back_inserter(v));
    for(auto& val : v)
        std::cout << val << " ";
}

void test_genalInsert()
{
    std::list<int> list;
    std::insert_iterator<std::list<int>> iter(list, list.begin());

    *iter = 1;
    *iter = 2;
    *iter = 3;

    std::inserter(list, list.begin()) = 222;
    for(auto& v : list)
        std::cout << v << " ";
}


void test_outStreamInter()
{
    std::ostream_iterator<int> iterINT(std::cout, "-");

    *iterINT = 1;
    iterINT++;
    *iterINT = 2;
    iterINT++;
    *iterINT = 3;
}

void test_inStreamInter()
{
    std::istream_iterator<int> iterINT(std::cin);
    std::istream_iterator<int> endIter;

    while(iterINT != endIter)
    {
        std::cout << "read something:" << *iterINT << std::endl;
        ++iterINT;
    }

}

void test_moveIter()
{
    std::list<int> list{1,2,3,4,5,6};
    std::vector<int> v;

    boost::format fmt("list size = %1% and v size = %2%");
    fmt % list.size() % v.size();
    std::cout << fmt << "\t" << fmt.size() << std::endl;

    std::vector<int> v2(std::make_move_iterator(list.begin()), std::make_move_iterator(list.end()));

    std::cout << boost::format("list size = %d and v2 size = %d") % list.size() % v2.size() << std::endl;
}


int main()
{
//    std::vector<int> v{12,2,3,22,34,32,11};
//    std::list<int> l{11,23,99};
//    std::sort(std::next(v.begin()), v.end());

//    for(const auto& val : v)
//        std::cout << val << " ";

//    auto iter = v.begin();
//    while(iter != v.end())
//    {
//        std::cout << *iter << " ";
//        std::advance(iter, 1);
//    }

//    auto iter_v = v.begin();
//    auto iter_l = l.begin();
//
//    std::cout << "before: " << *iter_v << "\t" << *iter_l << std::endl;
//
//    std::iter_swap(iter_v, iter_l);
//    std::cout << "after: " << *iter_v << "\t" << *iter_l << std::endl;


    test_moveIter();
    return 0;
}