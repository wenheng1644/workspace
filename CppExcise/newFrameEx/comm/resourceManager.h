
#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include "../netcomm/cmddispatch/DisPatcher.h"
#include "WorkRunner.h"

#include "vector"

enum NETWORK_TYPE
{
    NET_IO,
    NET_WORK
};

//资源管理类
class ResourceManager : public Singleton<ResourceManager>
{
public:

    ~ResourceManager() = default;
    ResourceManager();


    void onCallMessage(const netMsg& msg, user_ptr user);
    ioserver_tp& net_io() {return __netRunner.get_io();}
    size_t get_ioThreadSize() { return __netRunner.get_curthreadsize(); }

    void post(NETWORK_TYPE tp, std::function<void()> f);
private:
    DisPatcher __CmdDispatch;
    WorkRunner __netRunner;
    // WorkRunner m_workRunner;

    std::vector<WorkRunner> m_works;
    void init_WorkRunner();

    // void init_cmdDisPatch();

};


#endif