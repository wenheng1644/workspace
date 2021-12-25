#include "cardpool.h"
#include <fstream>
#include <regex> 
#include <assert.h>

cardpool::cardpool(string abs_file,string pro_file)
{
    loadConfig(abs_file);
    load_configpro(pro_file);
}

drawcard_data cardpool::get_drawcard(string line)
{
    drawcard_data data;

    int startIndex = 0;
    int nextIndex = -1;
    

    string partten = "";
    for(int i = 0;i < 3;i++)
        partten += "([[:alnum:]])*,";

    partten += "([[:alnum:]])*";

    regex r(partten);
    smatch res;
    
    if(!regex_match(line,res,r))
        return data;

    data.m_id = stoi(res[1]);
    data.m_name = res[2];
    data.m_quality = stoi(res[3]);
    data.m_pro = stoi(res[4]);

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
        map<int,drawcard_data> map_data = m_quality_cardpool[rare_quality];

        map_data[data.m_id] = data;
    }
}

rarepro_data cardpool::get_rarePro(string line)
{
    rarepro_data data;

    string partten = "([[:digit:]])+";
    partten += ",([[:digit:]])+";

    regex r(partten);
    smatch res;

    if(!regex_match(line,res,r))
        return data;

    data.m_quality = stoi(res[1]);
    data.m_pro = stoi(res[2]);

    return data;
}

bool cardpool::load_configpro(string pro_file)
{
    if(pro_file.empty())
        return false;

    ifstream in_profile(pro_file);

    if(!in_profile.is_open())
        return false;

    string line;

    while(getline(in_profile,line))
    {
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
    if(abs_file.empty())
        return false;

    ifstream in_file(abs_file);

    if(!in_file.is_open())
        return false;

    string line;
    while(getline(in_file,line))
    {
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

map<int,drawcard_data> cardpool::getCardPool(int rare)
{
    assert(rare >= 0 || rare <= 5);

    if(rare == 0)
        return m_cardpool;
    
    return m_quality_cardpool[rare];
}

int cardpool::getRareByRandom(size_t rand_num)
{
    int curRare = 1; //默认是普通品质
    size_t totalPro = 0;
    
    while(curRare <= RARE_QUALITY)
    {
        size_t curPro = m_RareProPool[curRare];

        totalPro += curPro;

        if(rand_num < totalPro)
            return curRare;

        curRare++;
    }

    return curRare;
}