#ifndef GATEUSERENG
#define GATEUSERENG

// #include "mutex"
#include "map"

#include "GateUser.h"
#include "commServer.h"
#include "commhead.h"

class GateUserEng
{
public:
    GateUserEng() = default;
    void push(gateUser_ptr user);
    void erase(boost::uuids::uuid onlyid);

    void run();

private:
    std::mutex m_GateUserMutex;
    std::map<boost::uuids::uuid ,gateUser_ptr>  m_GateUserLists;

    void processUser();
};

#endif
