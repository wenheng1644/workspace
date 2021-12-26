//
// Created by 文恒 on 2021/12/26.
//
#include <iostream>
#include <fstream>
#include <regex>

#include "../source/server/CardPool/cardpool.h"
#include "../source/server/drawCard/draw.h"

using namespace std;

void test_readFile();
void test_regex();

int main(void)
{
    draw drawObj;

    drawObj.showCardPoolInfos(1);

    vector<int> quality_count(6);

    int total_getCnt = 0;
    int getTimes = 0;
    while(getTimes < 10)
    {
        vector<drawcard_data> res = drawObj.tenGet();
        getTimes++;
        cout << endl;

        for(auto& e : res)
        {
            cout << "the output: ";

            cout << "id:\t" << e.m_id << "\t";
            cout << "name:\t" << e.m_name << "\t";
            cout << "rare:\t" << e.m_quality << "\t";
            cout << "pro:\t" << e.m_pro << endl;
            quality_count[e.m_quality]++;


            total_getCnt++;
        }
    }

    cout << "you getTimes:\t" << getTimes << "\ttotalCnt:\t" << total_getCnt << endl;
    for(int i = 1;i < quality_count.size();i++)
    {
        cout << "rare_quality:\t" << i << "\tcount:\t" << quality_count[i] << "\tprecise:\t" << (float)quality_count[i]/total_getCnt;
        cout << endl;
    }




//    test_readFile();
//    test_regex();
    return 0;
}

void test_readFile()
{
    ifstream in("..\\test.csv");

    if(in.is_open())
        cout << "is open!!" << endl;
    else
        cout << "open failure..." << endl;
}

void test_regex()
{
    string str = "101,normal_card1,1,8000";

    string partten = "([[:alnum:]]+)[\\s,](\\w+)[\\s,]([[:alnum:]]+)[\\s,]([[:alnum:]]+)";

    regex r(partten);

    smatch res;

    if(regex_search(str,res,r))
    {
        cout << "is match~~" << endl;
        cout << res[1].str() << endl;
        cout << res[2].str() << endl;
        cout << res[3].str() << endl;
        cout << res[4].str() << endl;
    }
    else
        cout << "not match..." << endl;

}