
#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include "../netcomm/cmddispatch/DisPatcher.h"


//资源管理类
class ResourceManager : public Singleton<ResourceManager>
{
public:
    ResourceManager();
    ~ResourceManager() = default;

    void init();
private:
    DisPatcher __CmdDispatch;

    void init_cmdDisPatch();
};


#endif