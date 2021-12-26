#include "cardpool.h"
#include <fstream>
#include <regex> 
#include <assert.h>
#include <random>
#include <ctime>

cardpool* cardpool::m_cardpool_ptr = nullptr;

cardpool::cardpool() : m_cardpool(map<int,drawcard_data>()),m_quality_cardpool(map<int,map<int,drawcard_data>>())
    ,m_RareProPool(6)
{
    loadConfig(CARDPOOL_CONFIG);
    load_configpro(RARE_CONFIG);
}

drawcard_data cardpool::get_drawcard(string line)
{
    drawcard_data data;

    string partten = "(\\w+)[\\s,](\\w+)[\\s,](\\w+)[\\s,](\\w+)";

    regex r(partten);
    smatch res;
    
    if(!regex_search(line,res,r))
        return data;

    data.m_id = stoi(res[1].str());
    data.m_name = res[2].str();
    data.m_quality = stoi(res[3].str());
    data.m_pro = stoi(res[4].str());

    return data;
}

void cardpool::load_configquality_drawcard_pool(drawcard_data& data)
{
    int rare_quality = data.m_quality;

    if(m_quality_cardpool[rare_quality].empty())
    {
        map<int,drawcard_data> map_data;
        map_data[data.m_id] = data;

        m_quality_cardpool[rare_quality] = map_data;
    }
    else
    {
        map<int,drawcard_data>& map_data = m_quality_cardpool[rare_quality];

        map_data[data.m_id] = data;
    }
}

rarepro_data cardpool::get_rarePro(string line)
{
    rarepro_data data;

    string partten = "([[:alnum:]]+)";
    partten += "[\\s,]+([[:alnum:]]+)";

    regex r(partten);
    smatch res;

    if(!regex_match(line,res,r))
        return data;

    data.m_quality = stoi(res[1].str());
    data.m_pro = stoi(res[2].str());

    return data;
}

bool cardpool::load_configpro(string pro_file)
{
    pro_file = string("..\\source\\comm\\config\\") + pro_file;
    if(pro_file.empty())
        return false;

    ifstream in_profile(pro_file);

    if(!in_profile.is_open())
        return false;

    string line;

    int row = 1;
    while(getline(in_profile,line))
    {
        if(row++ == 1) continue; //第一行跳过
        rarepro_data data = get_rarePro(line);

        if(data.m_pro == 0)
            return false;
        
        size_t rare = data.m_quality;

        m_RareProPool[rare] = data.m_pro;
    }

    in_profile.close();

    return true;
}

bool cardpool::loadConfig(string abs_file)
{
    abs_file = string("..\\source\\comm\\config\\") + abs_file;
    if(abs_file.empty())
        return false;

    ifstream in_file(abs_file,ios::in);

    if(!in_file.is_open())
        return false;

    string line;
    int row = 1;
    while(getline(in_file,line))
    {
        if(row++ == 1) continue;
        drawcard_data data = get_drawcard(line);

        if(data.m_id == -1)
            return false;

        int id = data.m_id;
        m_cardpool[id] = data;

        load_configquality_drawcard_pool(data);
    }
    in_file.close();
    return true;

}

map<int,drawcard_data> cardpool::getCardPool(size_t random_num)
{
    size_t rare = getRareByRandom(random_num);
//    cout << "print the rand_num: " << random_num << "\trare: " << rare << endl;

    assert(rare >= 0 || rare <= 5);
    if(rare == 0)
        return m_cardpool;

    return m_quality_cardpool[rare];
}

int cardpool::getRareByRandom(size_t rand_num)
{
    int curRare = 1; //默认是普通品质
    size_t totalPro = 0;

    if(m_RareProPool.empty())
        return -1;
    while(curRare <= RARE_QUALITY)
    {
        size_t curPro = m_RareProPool[curRare];

        totalPro += curPro;

        if(rand_num <= totalPro)
            return curRare;

        curRare++;
    }

    return curRare;
}

vector<drawcard_data> cardpool::getRandom_drawcard(int cnt)
{
    vector<drawcard_data> res;      //结果卡池

    //目前限定在单抽和十连抽
    assert(cnt == 1 || cnt == 10);

    static default_random_engine e(time(nullptr));
    static uniform_int_distribution<unsigned> u1(1,10000);

    for(int i = 0;i < cnt;i++)
    {
        size_t rand_num = u1(e);
        map<int,drawcard_data> rare_qualityCardPool = getCardPool(rand_num);

        vector<drawcard_data> tempPool; //临时卡池

        for(auto& e : rare_qualityCardPool)
        {
            if(!checkData(e.second))
            {
                cerr << "data error!!!" << endl;
                cerr << "id:\t" << e.second.m_id << "\tname:\t" << e.second.m_name << "\tquality:\t" << e.second.m_quality
                    << "\tpro:\t" << e.second.m_pro << endl;
                cerr << "data count: " << rare_qualityCardPool.size() << endl;
                print_Card(rare_qualityCardPool);
                exit(0);
            }
            tempPool.push_back(e.second);
        }

        unsigned int drawcard_count = tempPool.size();

//        if(drawcard_count == 0) continue;

        uniform_int_distribution<unsigned> u2(0,drawcard_count-1);

        int randomIndex = u2(e); //随机抽取索引
        drawcard_data data = tempPool[randomIndex];

        res.push_back(data);

    }

    return res;

}

void cardpool::print_Card(map<int,drawcard_data>& mapInfo)
{
    for(auto& e : mapInfo)
    {
        cout << "id:\t" << e.second.m_id << "\t";
        cout << "name:\t" << e.second.m_name << "\t";
        cout << "quality:\t" << e.second.m_quality << "\t";
        cout << "pro:\t" << e.second.m_pro << endl;
    }
}

void cardpool::show_AllCardPool()
{
    cout << "show all cardpool Info: " << endl;
    print_Card(m_cardpool);
}

void cardpool::show_RareCardPool()
{
    cout << "show rareCardPool: " << endl;
    for(auto& rareInfo : m_quality_cardpool)
    {
        int curRare = rareInfo.first;
        cout << "curRare: " << curRare << endl;

        print_Card(rareInfo.second);
    }
}

void cardpool::show_RarePro()
{
    int index = 0;
    for(auto& e : m_RareProPool)
    {
//        if(index++ == 0) continue;

        cout << "rare: " << index++ << "\tpro: " << e << endl;
    }
    cout << endl;
}

void cardpool::showCardInfo(int num)
{
    switch (num) {
        case 0:     show_AllCardPool();break;
        case 1:     show_RareCardPool();break;
        case 2:     show_RarePro();break;
        default:    show_AllCardPool();break;
    }
}

bool cardpool::checkData(drawcard_data& data)
{
    if(data.m_id < 100 || data.m_id > 600)
        return false;

    if(data.m_name.empty())
        return false;

    if(data.m_pro > 10000 || data.m_pro < 0)
        return false;

    if(data.m_quality <= 0 || data.m_quality > 5)
        return false;

    return true;
}