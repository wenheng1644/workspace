#include "draw.h"

cardpool* draw::cardPool_ptr = cardpool::GetCardPool();

vector<drawcard_data> draw::singleGet()
{
    drawcard_data data;
    if(!cardPool_ptr->isLoadCardPool())
        return vector<drawcard_data>();

    vector<drawcard_data> res = cardPool_ptr->getRandom_drawcard(1);

    if(res.size() != 1)
        return vector<drawcard_data>();

    data = res[0];


    return vector<drawcard_data>{data};
}

vector<drawcard_data> draw::tenGet()
{
    if(!cardPool_ptr->isLoadCardPool())
        exit(0);

    vector<drawcard_data> res = cardPool_ptr->getRandom_drawcard(10);

    return res;
}

void draw::showCardPoolInfos(int choice)
{
    cardPool_ptr->showCardInfo(choice);
}
