#ifndef FACTORY_H
#define FACTORY_H

#include "base_cmd.h"

class baseFactory
{
public:
    baseFactory() = default;
    virtual ~baseFactory() = default;

    virtual baseCmd* createCmd() = 0;

};


#endif