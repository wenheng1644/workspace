//
// Created by ADMIN on 2024/3/9.
//

#ifndef TEMPLATE_EX1_NEWTEMPLATE_H
#define TEMPLATE_EX1_NEWTEMPLATE_H


#include "deque"
#include "assert.h"

template<typename T, template<typename > typename All = std::deque>
class newStack {
    using iter_type = typename All<T>::iterator;

public:
    newStack() = default;

//    template<typename T2>
    newStack(std::initializer_list<T> list) : m_datas(list.begin(), list.end()) {}
    newStack(const newStack& other) : m_datas(other.m_datas.begin(), other.m_datas.end()) {}


    newStack& operator=(const newStack& other);


    class Interator
    {
    public:
        Interator(iter_type iter) : m_ptr(iter) {}

        T& operator*()
        {
            return *m_ptr;
        }

        Interator& operator++()
        {
            m_ptr++;
            return *this;
        }

        bool operator!=(const Interator& other)
        {
            return m_ptr != other.m_ptr;
        }

        bool operator==(const Interator& other)
        {
            return !(*this != other);
        }

        iter_type& data(){
            return m_ptr;
        }

    private:
        iter_type m_ptr;
    };

    T& top()
    {
        assert(empty());

        return m_datas.top();
    }

    void pop()
    {
        assert(empty());
        m_datas.pop_back();
    }

    void push(T v)
    {
        m_datas.push_back(v);
    }


    bool empty();

    size_t size();

    void erase(Interator bIter)
    {
        if(bIter == end()) return;

        m_datas.erase(bIter.data());
    }


    Interator begin()
    {
        return Interator(m_datas.begin());
    }

    Interator end()
    {
        return Interator(m_datas.end());
    }


private:
    All<T> m_datas;

};

template<typename T, template<typename > typename All>
newStack<T, All> &newStack<T, All>::operator=(const newStack &other) {

    m_datas.clear();

    m_datas.insert(m_datas.begin(), other.m_datas.begin(), other.m_datas.end());

    return *this;
}

template<typename T, template<typename > typename All>
size_t newStack<T, All>::size() {
    return m_datas.size();
}

template<typename T, template<typename > typename All>
bool newStack<T, All>::empty() {
    return m_datas.size() == 0;
}

template<typename T, template<typename > typename All>
typename newStack<T, All>::Interator begin(newStack<T, All>&  list)
{
    return list.begin();
}

template<typename T, template<typename > typename All>
typename newStack<T, All>::Interator end(newStack<T, All> & list)
{
    return list.end();
}




#endif //TEMPLATE_EX1_NEWTEMPLATE_H
