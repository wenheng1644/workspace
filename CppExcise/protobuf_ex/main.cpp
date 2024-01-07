#include <iostream>

#include "protomsg.pb.h"

#include "google/protobuf/descriptor.h"
#include "google/protobuf/dynamic_message.h"
//#include "google/protobuf/descriptor.pb.h"
#include <google/protobuf/compiler/importer.h>

#include "comm/DisPatcher.h"

void testprotobuf()
{
    using namespace persion;
    Persion p;
    p.set_name("徐伟镇");
    p.set_age(25);
    p.set_sex(0);

    ChatCmd cmd;
    cmd.mutable_p()->MergeFrom(p);
    cmd.set_time(time(nullptr));
    cmd.set_content("曹尼玛");


    std::string serstr = cmd.SerializeAsString();

    printf("serstr len = %d, size = %d\n", strlen(serstr.c_str()), serstr.size());

    ChatCmd sercmd;
    sercmd.ParseFromString(serstr);

    Persion p2 = sercmd.p();
    printf("name = %s, age = %d, sex = %d, time = %d, content = %s\n", p2.name().c_str(), p2.age(), p2.sex(), sercmd.time(), sercmd.content().c_str());


    Persion p_1;
    p_1.set_name("邝慧娴");
    p_1.set_age(25);
    p_1.set_sex(1);

    PersionList list;
    list.mutable_list()->insert(google::protobuf::MapPair<int32_t, Persion> (1, p_1));
    list.mutable_list()->insert(google::protobuf::MapPair<int32_t, Persion> (2, p2));

    std::string serlist = list.SerializeAsString();

    printf("serlist len = %d, size = %d\n", strlen(serlist.c_str()), serlist.size());

    PersionList parseList;
    parseList.ParseFromString(serlist);

    printf("map size = %d\n", parseList.list().size());

    auto& mapdata = parseList.list();
    for(auto& data : mapdata)
    {
        printf("index = %d, name = %s, sex = %d, age = %d\n", data.first, data.second.name().c_str(), data.second.sex(), data.second.age());
    }
}

void test_typename()
{
    using namespace google::protobuf;

    std::string typename1 = persion::Persion::descriptor()->full_name();

    std::cout << "typename1 = " << typename1 << std::endl;

    const Descriptor*  descriptor = DescriptorPool::generated_pool()->FindMessageTypeByName(typename1);

    std::cout << "FindMessageTypeByName() = " << descriptor << std::endl;
    std::cout << "persion::Persion::descriptor() = " << persion::Persion::descriptor() << std::endl;

    const Message* prototype = MessageFactory::generated_factory()->GetPrototype(descriptor);
    assert(prototype == &persion::Persion::default_instance());

    std::cout << "GetPrototype() = " << prototype << std::endl;
    std::cout << "default_instance() = " << &persion::Persion::default_instance() << std::endl;

    persion::Persion* obj = dynamic_cast<persion::Persion*>(prototype->New());
    assert(obj != nullptr);
    assert(obj != prototype);

    assert(typeid(*obj) == typeid(persion::Persion::default_instance()));
    std::cout << "prototype->New() = " << obj << std::endl;


    delete obj;

    std::cout << "delete obj" << std::endl;

    // while(true);

}

void onhandle_Persion(persion::Persion* p)
{
    printf("I am Persion | name = %s, age = %d, sex = %d\n", p->name().c_str(), p->age(), p->sex());
}

void onhandle_ChatCmd(persion::ChatCmd* p)
{
    printf("I am ChatCmd | time = %d, content = %s\n", p->time(), p->content().c_str());
}

void onhanlde_defalut(google::protobuf::Message* msg)
{
    printf("这是默认函数.... | type name = %s\n", msg->GetTypeName().c_str());
}

// void test_dispacther()
// {
//     using namespace google::protobuf;
//     DisPatcher disPatcher(onhanlde_defalut);

//     std::shared_ptr<CallBackT<persion::Persion>> c1(new CallBackT<persion::Persion>(onhandle_Persion));
//     disPatcher.registerCb<persion::Persion>(persion::Persion::descriptor(), c1);

//     // persion::Persion p1 = persion::Persion::default_instance();
//     google::protobuf::DynamicMessageFactory f;
//     const google::protobuf::Message* p1 = f.GetPrototype(persion::Persion::GetDescriptor());
//     persion::Persion* dyp = dynamic_cast<persion::Persion*>(p1->New());
//     dyp->set_age(25);
//     dyp->set_name("徐伟镇");
//     dyp->set_sex(1);
//     std::shared_ptr<google::protobuf::Message> m1(dyp);
//     // std::shared_ptr<persion::Persion> m1(dyp);
//     // m1->set_age(25);
//     // m1->set_name("徐伟镇");
//     // m1->set_sex(1);

//     // persion::ChatCmd chat1 = persion::ChatCmd::default_instance();
//     const google::protobuf::Message* chat1 = f.GetPrototype(persion::ChatCmd::GetDescriptor());
//     persion::ChatCmd * chatcmd = dynamic_cast<persion::ChatCmd*>(chat1->New());
//     chatcmd->set_content("fuck you");
//     chatcmd->set_time(111);
//     std::shared_ptr<persion::ChatCmd> m2(chatcmd);

//     // m2->set_time(99);
//     // m2->set_content("fuck you");
//     disPatcher.onCallMessage(m1);
//     disPatcher.onCallMessage(m2);
// }

void DeleteProtoBuf(google::protobuf::Message* msg)
{   
    assert(msg != nullptr);
    delete msg;
}

google::protobuf::Message* getMessageByName(const std::string& classname)
{
    using namespace google::protobuf;

    printf("当前name = %s\n", classname.c_str());


    const Descriptor* desc = DescriptorPool::generated_pool()->FindMessageTypeByName(classname);
    assert(desc != nullptr);

    const Message* prototype = MessageFactory::generated_factory()->GetPrototype(desc);

    Message* p = prototype->New();

    assert(p != prototype);

    return p;
}

void test_dyn()
{
    DisPatcher disPatcher(onhanlde_defalut);

    std::shared_ptr<CallBackT<persion::Persion>> c1(new CallBackT<persion::Persion>(onhandle_Persion));
    disPatcher.registerCb<persion::Persion>(persion::Persion::descriptor(), c1);



    google::protobuf::Message* proto = getMessageByName(persion::Persion::descriptor()->full_name());
    google::protobuf::Message* obj1 = proto->New();
    persion::Persion* p1 = dynamic_cast<persion::Persion*>(obj1);
    p1->set_age(25);
    p1->set_name("徐伟镇");
    p1->set_sex(1);

    google::protobuf::Message* proto1 = getMessageByName(persion::ChatCmd::descriptor()->full_name());
    google::protobuf::Message* obj2 = proto1->New();

    std::cout << "proto address = " << proto << std::endl;
    std::cout << "ptr address = " << p1 << std::endl;
    std::cout <<  p1->GetTypeName() << std::endl;

    disPatcher.onCallMessage(obj1);
    disPatcher.onCallMessage(obj2);
    std::cout << "1111111111111111111111" << std::endl;
}

int main() {
    test_dyn();
    return 0;
}
