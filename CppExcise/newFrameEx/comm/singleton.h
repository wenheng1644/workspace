#ifndef SINGLETON
#define SINGLETON


#include "mutex"

template<typename T>
class Singleton
{
public:
    static T* getObj()
    {
        std::lock_guard<std::mutex> gl(m_singletonM);
        if(!m_obj)
            m_obj = new T;
        return m_obj;
    }

protected:
    Singleton() = default;
    virtual ~Singleton()
    {
        if(m_obj) delete m_obj;
    }

    static T* m_obj;
    static std::mutex m_singletonM;
};

template<typename T>
T* Singleton<T>::m_obj = nullptr;

template<typename  T>
std::mutex Singleton<T>::m_singletonM;

#endif