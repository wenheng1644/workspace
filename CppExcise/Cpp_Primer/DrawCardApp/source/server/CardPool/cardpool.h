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
    
    static cardpool* GetCardPool()
    {
        if(!m_cardpool_ptr)
        {
            m_cardpool_ptr = new cardpool();
        }
        
        return m_cardpool_ptr;
    }

    //是否已加载卡池
    bool isLoadCardPool() { return !m_cardpool.empty(); }

    //根据需要显示相应的内容
    //num = 0: 显示所有卡池信息
    //num = 1: 显示稀有度卡池信息
    //num = 2: 显示稀有度概率信息
    void showCardInfo(int num = 0);

    //抽卡，默认是单抽
    vector<drawcard_data> getRandom_drawcard(int cnt = 1);
private:
    //静态指针
    static cardpool* m_cardpool_ptr;

    //所有卡池
    map<int,drawcard_data> m_cardpool;                      

    //不同稀有度的卡池  稀有度作为key，对应卡池为value
    map<int,map<int,drawcard_data>> m_quality_cardpool;

    //不同稀有度所对应的概率
    vector<int> m_RareProPool;

    cardpool();

    //切割一行字符串数据
    drawcard_data get_drawcard(string line);

    //切割一行字符串数据获得稀有度概率
    rarepro_data get_rarePro(string line);

    //加载卡池配置文件
    bool loadConfig(string abs_file);

    //加载对应不同稀有度的卡池
    void load_configquality_drawcard_pool(drawcard_data& data);

    //加载概率配置文件
    bool load_configpro(string pro_file);

    //通过随机数返回对应稀有度
    int getRareByRandom(size_t rand_num);

    //获取对应稀有度卡池
    //rand_num随机数 
    map<int,drawcard_data> getCardPool(size_t rand_num);

    //打印卡池
    void print_Card(map<int,drawcard_data>& mapInfo);
    void show_RareCardPool();
    void show_AllCardPool();
    void show_RarePro();

    //检查数据的合法性
    bool checkData(drawcard_data& data);
};

#endif