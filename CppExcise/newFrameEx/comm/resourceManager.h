
#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include "../netcomm/cmddispatch/DisPatcher.h"
#include "WorkRunner.h"


//资源管理类
class ResourceManager : public Singleton<ResourceManager>
{
public:

    ~ResourceManager() = default;
    ResourceManager();


    void onCallMessage(const netMsg& msg, user_ptr user);
    ioserver_tp& net_io() {return __netRunner.get_io();}
    size_t get_ioThreadSize() { return __netRunner.get_curthreadsize(); }

    WorkRunner m_workRunner;
private:
    DisPatcher __CmdDispatch;
    WorkRunner __netRunner;
    
    // void init();

    // void init_cmdDisPatch();

};


#endif