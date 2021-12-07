/**
 * @file temp_Blob.h
 * @author xwz
 * @brief 尝试写一个模板类(下次找个时间再写)
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TEMP_BLOB
#define TEMP_BLOB

#include <initializer_list>
#include <memory>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class Blob{
public:
    Blob();
    Blob(initializer_list<T> li);

    int size() const;
    bool empty() const { return data->empty(); }

    void push_back(const T& val) { data->push_back(val); }

private:
    shared_ptr<vector<T>> data;

    void check(int i,const string& msg);
};

#endif