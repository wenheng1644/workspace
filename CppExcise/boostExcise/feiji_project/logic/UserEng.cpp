//
// Created by wenheng on 23-6-25.
//

#include "UserEng.h"
template<typename  T>
T* mySington<T>::m_obj = nullptr;

template<> UserEng* mySington<UserEng>::m_obj = nullptr;