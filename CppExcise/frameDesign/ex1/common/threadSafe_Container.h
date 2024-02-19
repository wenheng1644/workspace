//
// Created by wenheng on 23年9月23日.
//

#ifndef EX1_THREADSAFE_CONTAINER_H
#define EX1_THREADSAFE_CONTAINER_H

#include "deque"
#include "mutex"
#include "shared_mutex"
#include "condition_variable"

#include "memory"
#include "iostream"
#include "algorithm"
#include "functional"

template<typename T>
class threadSafe_Container {
public:
    threadSafe_Container() = default;

    class iterator
    {
    public:
        iterator(typename std::deque<std::shared_ptr<T>>::iterator it) : m_it_(it) {}

        std::shared_ptr<T>& operator*()
        {
            return *m_it_;
        }

        iterator& operator++()
        {
            m_it_++;
            return *this;
        }

        bool operator==(const iterator& other)
        {
            return m_it_ == other.m_it_;
        }

        bool operator!=(const iterator& other)
        {
            return !(*this == other);
        }

    private:
        typename std::deque<std::shared_ptr<T>>::iterator m_it_;
    };

    std::shared_mutex m_mutex_;
    std::condition_variable_any m_cond_;

    bool push(std::shared_ptr<T> data);
    bool empty();
    bool isExist(std::shared_ptr<T> data);
    size_t size();

    void getDatas(std::deque<std::shared_ptr<T>>& queue);
    void getCopyDatas(std::deque<std::shared_ptr<T>>& queue);

    std::shared_ptr<T> pop();
    bool remove(std::shared_ptr<T> data);

    iterator begin()
    {
        return iterator(m_datas_.begin());
    }

    iterator end()
    {
        return iterator(m_datas_.end());
    }

//private:
    std::deque<std::shared_ptr<T>> m_datas_;


};

template<typename T>
bool threadSafe_Container<T>::push(std::shared_ptr<T> data)
{
    std::unique_lock<std::shared_mutex> uniqueLock_l(m_mutex_);
    auto iter = std::find_if(m_datas_.begin(), m_datas_.end(), [=](std::shared_ptr<T> a)
    {
        if(*a == *data) return true;
        return false;
    });

    if(iter != m_datas_.end())
        return false;

    m_datas_.push_back(data);
    m_cond_.notify_one();
    return true;
}

template<typename T>
std::shared_ptr<T>  threadSafe_Container<T>::pop()
{
    std::unique_lock<std::shared_mutex> uniqueLock_l(m_mutex_);
    if(m_datas_.empty()) return std::shared_ptr<T>();

    std::shared_ptr<T> data = m_datas_.front();
    m_datas_.pop_front();

    return  data;
}

template<typename T>
bool threadSafe_Container<T>::empty()
{
    std::shared_lock<std::shared_mutex> sharedLock(m_mutex_);
    return m_datas_.empty();
}

template<typename T>
bool threadSafe_Container<T>::isExist(std::shared_ptr<T> data)
{
    std::shared_lock<std::shared_mutex> sharedLock(m_mutex_);

    auto iter = std::find_if(m_datas_.begin(), m_datas_.end(), [=](std::shared_ptr<T> a)
    {
        if(*a == *data) return true;
        return false;
    });

    return iter != m_datas_.end();
}

template<typename T>
bool threadSafe_Container<T>::remove(std::shared_ptr<T> data)
{
    std::unique_lock uniqueLock(m_mutex_);

    auto iter = std::remove_if(m_datas_.begin(), m_datas_.end(), [=](std::shared_ptr<T> a)
    {
        if(*a == *data) return true;
        return false;
    });

    if(iter == m_datas_.end()) return false;

    m_datas_.erase(iter, m_datas_.end());

    return true;

}

template<typename  T>
void threadSafe_Container<T>::getDatas(std::deque<std::shared_ptr<T>>& queue)
{
    std::unique_lock uniqueLock(m_mutex_);
    queue.swap(m_datas_);
}

template<typename  T>
void threadSafe_Container<T>::getCopyDatas(std::deque<std::shared_ptr<T>> &queue)
{
    std::unique_lock uniqueLock(m_mutex_);
    queue.clear();
    queue.resize(m_datas_.size());
    std::copy(m_datas_.begin(), m_datas_.end(), queue.begin());
}

template<typename T>
size_t threadSafe_Container<T>::size()
{
    std::shared_lock<std::shared_mutex> sharedLock(m_mutex_);
    return m_datas_.size();
}
#endif //EX1_THREADSAFE_CONTAINER_H
