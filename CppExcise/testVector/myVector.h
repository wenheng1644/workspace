//
// Created by wenheng on 22-10-30.
//
/*
 * 关键是处理数据边界以及内存管理
 */

#ifndef TESTVECTOR_MYVECTOR_H
#define TESTVECTOR_MYVECTOR_H

#include <memory>
#include <iostream>
#include "exception"
#include <initializer_list>

template<typename T>
class myVector {
public:
    typedef T   value_type;
    typedef T&  value_ref;
    typedef T*  value_point;
public:
    myVector();
    myVector(const std::initializer_list<T>& list){
        list_init(list);
    }
    myVector(size_t cnt, const T& v);
    myVector(const myVector<T>& cpVector);
    ~myVector();

    value_ref operator[](int pos)
    {
        if(pos < 0)
            throw std::range_error("pos is neg");
        if(pos >=  size())
            throw std::range_error("pos is too big");

        return *(m_first + pos);
    }
    value_point begin() { return m_first;}
    value_point end() { return m_finish;}

    size_t size(){ return m_finish - m_first;}
    size_t capactiy() { return m_endMemory - m_first;}
    bool empty() { return m_first == m_finish;}
    void push_back(const T& v);
    void insert(value_point pos, const T& v);
    void insert(value_point pos, const std::initializer_list<T>& list);
    value_point find(const value_type& v);
private:
    std::allocator<T> m_allocator;

    value_point m_first;
    value_point m_finish;
    value_point m_endMemory;


    void list_init(const std::initializer_list<T>& list);
    void fill_init(size_t cnt, const T& v);
    value_point allocte_memory(size_t cnt)
    {
        value_point point = m_allocator.allocate(cnt);
        return point;
    }

    void destroyAll(value_point first, size_t n = 1);
    void freeMemory(value_point first, size_t n);
    void _insert_list(value_point pos, const std::initializer_list<T>& list);
};



template<typename T>
myVector<T>::myVector(): m_first(nullptr), m_finish(nullptr), m_endMemory(nullptr){

}

template<typename T>
myVector<T>::myVector(size_t cnt, const T &v) {
    fill_init(cnt, v);
}

template<typename T>
myVector<T>::myVector(const myVector<T> &cpVector) {
    size_t cpSize = cpVector.m_finish - cpVector.m_first;

    value_point newPos = allocte_memory(cpSize);
    for(int i = 0; i < cpSize; i++)
    {
        m_allocator.construct(newPos + i, *(cpVector.m_first + i));
    }
    m_first = newPos;
    m_finish = m_first + cpSize;
    m_endMemory = m_finish;
}

template<typename T>
myVector<T>::~myVector() {
    size_t size = m_finish - m_first;
    for(int i = 0; i < size; i++)
        m_allocator.destroy(m_first+i);

    size_t all = m_endMemory - m_first;
    m_allocator.deallocate(m_first, all);
}

template<typename T>
void myVector<T>::fill_init(size_t cnt, const T &v) {
    value_point temp  = allocte_memory(cnt);
    for(int i = 0; i < cnt; i++)
        *(temp + i) = v;

    m_first = temp;
    m_finish = temp + cnt;
    m_endMemory = m_finish;
}


template<typename T>
void myVector<T>::list_init(const std::initializer_list<T>& list) {
    size_t cnt = list.size();
    if(cnt <= 0)
        throw std::range_error("index error");

    value_point newPos = allocte_memory(cnt);
    for(int i = 0; i < cnt; i++)
    {
        m_allocator.construct(newPos+i, *(list.begin()+i));
    }
    m_first = newPos;
    m_finish = m_first + cnt;
    m_endMemory = m_finish;
}

template<typename T>
void myVector<T>::destroyAll(myVector::value_point first, size_t n) {
    for(int i = 0; i < n; i++)
        m_allocator.destroy(first+i);
}

template<typename T>
void myVector<T>::freeMemory(myVector::value_point first, size_t n) {
    destroyAll(first, n);
    m_allocator.deallocate(first, n);
}

template<typename T>
void myVector<T>::push_back(const T &v) {
    _insert_list(m_finish, {v});
}

template<typename T>
void myVector<T>::_insert_list(myVector::value_point pos, const std::initializer_list<T>& list) {
    size_t curCap = capactiy();
    size_t curSize = size();
    size_t leftCap = curCap - curSize;
    int needCap = list.size() - leftCap;
    if(needCap > 0)
    {
        size_t alloc_Cap = (curCap * 2 < curCap + needCap) ? (curCap * 2 + needCap) : (curCap * 2);
        value_point newPos = allocte_memory(alloc_Cap);
        value_point beforePos = std::uninitialized_copy(m_first, pos, newPos);
        value_point curPos = std::uninitialized_copy(list.begin(),  list.end(), beforePos);
        std::uninitialized_copy(pos, m_finish, curPos);

        freeMemory(m_first, curCap);
        m_first = newPos;
        m_finish = newPos + curCap + needCap;
        m_endMemory = m_first + alloc_Cap;
    }
    else
    {
        std::uninitialized_fill(m_finish, m_finish+list.size(), *(m_finish - 1));
        std::copy_backward(pos, m_finish, m_finish+list.size()-1);
        std::copy(list.begin(), list.end(), pos);

        m_finish += list.size();
    }

}

template<typename T>
void myVector<T>::insert(myVector::value_point pos, const T &v) {
    _insert_list(pos, {v});
}

template<typename T>
void myVector<T>::insert(myVector::value_point pos, const std::initializer_list<T> &list) {
    _insert_list(pos, list);
}

template<typename T>
T* myVector<T>::find(const value_type& v) {
    for(auto first = m_first; first != m_finish; first++)
    {
        if(*first == v)
            return first;
    }
    return nullptr;
}


#endif //TESTVECTOR_MYVECTOR_H
