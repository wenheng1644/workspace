//
// Created by wenheng on 23-7-2.
//

#include "base_cmd.h"
#include "playerSys_cmd.h"

u_short playerConnectCmd::getConnectCheckValue(const playerConnectCmd& cmd)
{
    u_char v1 = cmd.v1 & 0x0f;
    u_char v2 = ((cmd.v2 & 0x0f) << 2) & 0x0f;
    u_char v3 = (cmd.v3 & 0x0f) >> 2;

    return v1 ^ (v2 << 2) ^ (v3 << 6) | 0x01;
}

bool playerConnectCmd::isvaild() {

    u_char value = getConnectCheckValue(*this);
    if(value == checkvalue) return true;

    return false;
}
