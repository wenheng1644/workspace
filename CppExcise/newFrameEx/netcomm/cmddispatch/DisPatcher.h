//
// Created by wenheng on 23年12月23日.
//

#ifndef PROTOBUF_EX_DISPATCHER_H
#define PROTOBUF_EX_DISPATCHER_H

#include "map"

#include "CallBack.h"

#include "../netcommhead.h"
#include "../comm/singleton.h"

class DisPatcher : public boost::noncopyable, public Singleton<DisPatcher> {
public:
    DisPatcher();

    void setDefalutCB(std::function<void(google::protobuf::Message*)> cb) {__defalutcb = cb;}
    
    template<typename T>
    void registerCb(const google::protobuf::Descriptor* key, std::shared_ptr<CallBackT<T>> cb);

    void onCallMessage(google::protobuf::Message* msg, user_ptr user);
private:
    std::map<const google::protobuf::Descriptor*, CB> __cb_hash;

    std::function<void(google::protobuf::Message*)> __defalutcb;
};

template<typename T>
void DisPatcher::registerCb(const google::protobuf::Descriptor *key, std::shared_ptr<CallBackT<T>> cb)
{
    __cb_hash[key] = cb;
}


#endif //PROTOBUF_EX_DISPATCHER_H
