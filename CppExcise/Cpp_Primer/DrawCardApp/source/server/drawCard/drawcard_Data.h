#ifndef _DRAWCARD_DATA_
#define _DRAWCARD_DATA_

#include <string>
using namespace std;

#define CONFIG_COUNT 4
#define RARE_QUALITY 5

//卡的数据结构
struct drawcard_data
{
    size_t     m_id;    //卡id
    string  m_name;     //卡名
    size_t  m_quality;  //卡品质（1-5）
    int  m_pro;      //卡概率

    drawcard_data() : m_id(-1),m_name(""),m_quality(-1),m_pro(-1) {}
};

//稀有度的数据结构
struct rarepro_data
{
    size_t m_quality;
    int    m_pro; 

    rarepro_data() : m_quality(0),m_pro(0) {}
};

#endif