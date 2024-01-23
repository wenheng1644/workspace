//
// Created by wenheng on 23年12月23日.
//

#ifndef PROTOBUF_EX_CALLBACK_H
#define PROTOBUF_EX_CALLBACK_H

#include "functional"
#include "../netcommhead.h"

// typedef std::shared_ptr<google::protobuf::Message> Message_Ptr;
class CallBack {
public:
    CallBack() = default;
    virtual  ~CallBack() {}

    virtual void onMessage(google::protobuf::Message* msg) = 0;
};

template<typename T>
class CallBackT : public CallBack
{
public:
    CallBackT(std::function<void(T*)> cb) : __cb(cb) {}
    virtual ~CallBackT() {}

    virtual void onMessage(google::protobuf::Message* msg) override;
private:
    std::function<void(T*)> __cb;
};

typedef std::shared_ptr<CallBack> CB;

template<typename T>
void CallBackT<T>::onMessage(google::protobuf::Message* msg)
{
    if(!msg)
    {
        printf("type name msg(%s) is null\n", msg->GetTypeName().c_str());
        return;
    }
    // using namespace google::protobuf;
    // Message* p = msg.get();
    T* concertP = dynamic_cast<T*>(msg);
    assert(concertP != nullptr);
    // std::shared_ptr<T> concertObj(concertP);
    __cb(concertP);
}


#endif //PROTOBUF_EX_CALLBACK_H
