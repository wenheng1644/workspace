//
// Created by нд╨Ц on 2022/6/30.
//

#include "myAlgorithm.h"
#include <iostream>
#include <ctime>
#include <algorithm>


int main()
{
    std::vector<int> nums{31,4,5,62,34,232,57,11,0,56,54,33,35,11,57,66,62};

//    algorithm_sort::select_sort(nums);
//    partion(nums, 0, nums.size()-1);

//    algorithm_sort::merge_sort(nums, 0, nums.size() - 1);
//    auto issort = std::is_sorted(nums.begin(), nums.end(), [](int a, int b){ return a > b;});
//    if(issort)
//        std::cout << "yes" << std::endl;
//    else
//        std::cout << "no" << std::endl;
//    for(auto& v : nums)
//        std::cout << v << " ";
//    std::cout << std::endl;


    auto iter = std::min_element(nums.begin(), nums.end());
    std::cout << "min value:\t" << *iter << std::endl;

    auto pairIter = std::minmax_element(nums.begin(), nums.end());
    std::cout << "min value:\t" << *pairIter.first << "\tmax value:\t" << *pairIter.second << std::endl;

    int cnt = std::count_if(nums.begin(), nums.end(), [](int a){ return a >= 50;} );
    std::cout << "cnt:\t" << cnt << std::endl;

    auto iter_search = std::search_n(nums.begin(), nums.end(), 3, 50, [](int a , int v){ return a >= v;});
    if(iter_search != nums.end())
        std::cout << "find it\t" << *iter_search << std::endl;


    return 0;
}