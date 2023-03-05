//
// Created by нд╨Ц on 2022/6/30.
//

#ifndef MYALGORITHM_MYALGORITHM_H
#define MYALGORITHM_MYALGORITHM_H

#include <vector>
#include <ctime>
#include <iostream>

int partion(std::vector<int>& nums, int left, int right);

void megre(std::vector<int>& nums, int left, int mid, int right);

namespace algorithm_sort
{
    void select_sort(std::vector<int>& nums);

    void quick_sort(std::vector<int>& nums, int left, int right);

    void merge_sort(std::vector<int>& nums, int left, int right);
}

#endif //MYALGORITHM_MYALGORITHM_H
