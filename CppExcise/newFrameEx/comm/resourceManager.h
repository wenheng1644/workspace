
#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include "../netcomm/cmddispatch/DisPatcher.h"


//资源管理类
class ResourceManager : public Singleton<ResourceManager>
{
public:
    ResourceManager();
    ~ResourceManager() = default;

    void onCallMessage(google::protobuf::Message* msg);
private:
    DisPatcher __CmdDispatch;
    void init();

    void init_cmdDisPatch();
};


#endif