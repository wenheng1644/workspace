#ifndef GATECMDHEAD
#define GATECMDHEAD

#include "ConnectionCmd/Connection.h"


#define MAKEPROTO(id,subid) ((subid<<8)|id)


#define CONNECTIONSYS       1           //连接系统 id=1



//连接请求
#define CONNECTION_REQ      MAKEPROTO(CONNECTIONSYS,CONNECTION_CMD)


#endif 