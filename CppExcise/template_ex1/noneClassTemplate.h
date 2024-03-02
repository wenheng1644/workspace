//
// Created by wenheng on 24-2-28.
//

#ifndef TEMPLATE_EX1_NONECLASSTEMPLATE_H
#define TEMPLATE_EX1_NONECLASSTEMPLATE_H

#include "iostream"
#include "array"

template<typename T, auto len>
class Stack
{
public:
    using size_tp = decltype(len);
    using value_tp = T;

    Stack();
    bool push(T v);
    bool pop();

    T top() const;

    size_tp size() const;
    size_tp max_size() const;

private:
    std::array<T, len> m_datas;
    size_tp  m_nowLen;
};

template<typename T, auto len>
typename Stack<T, len>::size_tp Stack<T, len>::max_size() const {
    return len;
}

template<typename T, auto len>
typename Stack<T, len>::size_tp Stack<T, len>::size() const
{
    return m_nowLen;
}

template<typename T, auto len>
T Stack<T, len>::top() const
{
    if(m_nowLen <= 0)
        return T();

    return m_datas[m_nowLen-1];
}

template<typename T, auto len>
bool Stack<T, len>::pop()
{
    if(m_nowLen <= 0) return false;

    m_datas[--m_nowLen] = T();
    return true;
}

template<typename T, auto len>
bool Stack<T, len>::push(T v)
{
    if(m_nowLen >= len) return false;

    m_datas[m_nowLen++] = v;
    return true;
}

template<typename T, auto len>
Stack<T, len>::Stack() : m_nowLen(0)
{

}


#endif //TEMPLATE_EX1_NONECLASSTEMPLATE_H
