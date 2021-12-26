#include "draw.h"

cardpool* cardPool_ptr = cardpool::GetCardPool();

drawcard_data draw::singleGet()
{
    drawcard_data data;
    if(!cardPool_ptr->isLoadCardPool())
        return data;

    vector<drawcard_data> res = cardPool_ptr->getRandom_drawcard(1);

    if(res.size() != 1)
        return data;

    data = res[0];

    return data;
}

vector<drawcard_data> draw::tenGet()
{
    vector<drawcard_data> res;

    if(!cardPool_ptr->isLoadCardPool())
        return res;

    res = cardPool_ptr->getRandom_drawcard(10);

    return res;
}

void draw::showCardPoolInfos(int choice)
{
    cardPool_ptr->showCardInfo(choice);
}