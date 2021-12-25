#ifndef _CARDPOOL_
#define _CARDPOOL_

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "../drawCard/drawcard_Data.h"

using namespace std;

class draw;

class cardpool{
    friend draw;
public:
    cardpool(string abs_file,string pro_file);
    ~cardpool();

    bool loadConfig(string abs_file);

    //是否已加载卡池
    bool isLoadCardPool() { return !m_cardpool.empty(); }
    
    //获取对应稀有度卡池 
    //rare默认值为0，则是全部卡池
    map<int,drawcard_data> getCardPool(int rare = 0);

private:
    map<int,drawcard_data> m_cardpool;                      //所有卡池

    //不同稀有度的卡池  稀有度作为key，对应卡池为value
    map<int,map<int,drawcard_data>> m_quality_cardpool;

    //不同稀有度所对应的概率
    vector<int> m_RareProPool;

    //切割一行字符串数据
    drawcard_data get_drawcard(string line);

    //切割一行字符串数据获得稀有度概率
    rarepro_data get_rarePro(string line);

    //加载对应不同稀有度的卡池
    void load_configquality_drawcard_pool(drawcard_data& data);

    //加载概率配置文件
    bool load_configpro(string pro_file);

    //通过随机数返回对应稀有度
    int getRareByRandom(size_t rand_num);
};


#endif