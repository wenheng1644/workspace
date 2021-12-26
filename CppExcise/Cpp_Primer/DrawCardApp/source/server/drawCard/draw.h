#ifndef _DRAW_
#define _DRAW_

#include <vector>
#include <string>

#include "drawcard_Data.h"
#include "../CardPool/cardpool.h"

using namespace std;



//抽卡类
class draw{
public:
    draw() {}
    ~draw() {}

    //单抽
    drawcard_data singleGet();

    //十连抽
    vector<drawcard_data> tenGet();

    //显示卡池信息
    void showCardPoolInfos(int choice = 0);
};




#endif