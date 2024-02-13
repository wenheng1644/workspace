//
// Created by wenheng on 23年12月23日.
//

#ifndef PROTOBUF_EX_CALLBACK_H
#define PROTOBUF_EX_CALLBACK_H

#include "functional"
#include "../netcommhead.h"

#include "../../logic/user.h"
// typedef std::shared_ptr<google::protobuf::Message> Message_Ptr;
class CallBack {
public:
    CallBack() = default;
    virtual  ~CallBack() {}

    virtual void onMessage(const netMsg& msg, user_ptr user) = 0;
};

template<typename T>
class CallBackT : public CallBack
{
public:
    CallBackT(std::function<void(const T*, user_ptr)> cb) : __cb(cb) {}
    virtual ~CallBackT() {}

    virtual void onMessage(const netMsg& msg, user_ptr user) override;
private:
    std::function<void(const T*, user_ptr)> __cb;
};

typedef std::shared_ptr<CallBack> CB;

template<typename T>
void CallBackT<T>::onMessage(const netMsg& msg, user_ptr user)
{
    // if(!msg)
    // {
    //     printf("type name msg(%s) is null\n", msg->GetTypeName().c_str());
    //     return;
    // }
    // using namespace google::protobuf;
    // Message* p = msg.get();
    T cmd = parseSerlizeStr<T>(msg.datas);

    // const T* concertP = dynamic_cast<const T*>(msg);
    // assert(concertP != nullptr);
    // std::shared_ptr<T> concertObj(concertP);
    __cb(&cmd, user);
}


#endif //PROTOBUF_EX_CALLBACK_H
