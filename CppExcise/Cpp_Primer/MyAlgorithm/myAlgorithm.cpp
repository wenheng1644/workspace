//
// Created by 文恒 on 2022/6/30.
//
#include "myAlgorithm.h"

int partion(std::vector<int>& nums, int left, int right)
{
    srand(time(nullptr));
    int range_value = rand() % (right - left  + 1);
    int rangeIndex = left + range_value;
    int provt = nums[rangeIndex];

    std::swap(nums[rangeIndex], nums[right]);

    int pos = left; //小于基准值区域索引（开区间）

    while(left <= right)
    {
        if(nums[left] < provt)
        {
            std::swap(nums[left], nums[pos]);
            pos++;
        }
        left++;
    }
    std::swap(nums[right], nums[pos]);
//    std::cout << "provt:\t" << provt << " randIndex:\t" << randIndex << " pos:\t" << pos << std::endl;
    return pos;
}

void megre(std::vector<int>& nums, int left, int mid, int right)
{
    std::vector<int> temp(right - left + 1);
    int p1 = left;
    int p2 = mid + 1;

    int index = 0;
    while(p1 <= mid && p2 <= right)
    {
        if(nums[p1] > nums[p2])
        {
            temp[index++] = nums[p2];
            p2++;
        }
        else
        {
            temp[index++] = nums[p1];
            p1++;
        }
    }

    while(p1 <= mid)
    {
        temp[index++] = nums[p1++];
    }

    while(p2 <= right)
    {
        temp[index++] = nums[p2++];
    }

    for(int i = 0; i < right - left + 1; i++)
        nums[left + i] = temp[i];

}

void algorithm_sort::select_sort(std::vector<int> &nums)
{
    int len = nums.size();

    for(int i = 0; i < len; i++)
    {
        int maxIndex = i;
        int maxValue = nums[maxIndex];
        for(int j = i; j < len; j++)
        {
            if(maxValue < nums[j])
            {
                maxIndex = j;
                maxValue = nums[j];
            }
        }
        std::swap(nums[i], nums[maxIndex]);
    }

}

void algorithm_sort::quick_sort(std::vector<int> &nums, int left, int right)
{
    if(left >= right)
        return;

    int pos = partion(nums, left, right);

    quick_sort(nums, left, pos-1);
    quick_sort(nums,pos + 1, right);
}

void algorithm_sort::merge_sort(std::vector<int> &nums, int left, int right)
{
    if(left >= right)
        return;

    int mid = left +((right - left) >> 1);

    merge_sort(nums, left, mid);
    merge_sort(nums, mid + 1, right);

    megre(nums, left, mid, right);
}