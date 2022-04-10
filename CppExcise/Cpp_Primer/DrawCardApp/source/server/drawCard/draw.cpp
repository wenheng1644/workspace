#include "draw.h"
#include "../myLog/mylog.h"

cardpool* draw::cardPool_ptr = cardpool::GetCardPool();

vector<drawcard_data> draw::singleGet(bool isLog)
{
    drawcard_data data;
    if(!cardPool_ptr->isLoadCardPool())
        return vector<drawcard_data>();

    vector<drawcard_data> res = cardPool_ptr->getRandom_drawcard(1);

    if(res.size() != 1)
        return vector<drawcard_data>();

    data = res[0];

    //日志记录
    if(isLog)
    {
        mylog* logptr = mylog::getSingleton();
        logptr->write(res);
    }

    return vector<drawcard_data>{data};
}

vector<drawcard_data> draw::tenGet(bool isLog)
{
    if(!cardPool_ptr->isLoadCardPool())
        exit(0);

    vector<drawcard_data> res = cardPool_ptr->getRandom_drawcard(10);

    //日志记录
    if(isLog)
    {
        mylog* logptr = mylog::getSingleton();
        logptr->write(res);
    }
    return res;
}

void draw::showCardPoolInfos(int choice)
{
    cardPool_ptr->showCardInfo(choice);
}
