//
// Created by �ĺ� on 2021/12/26.
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

    vector<int> quality_count(6,0);

    int total_getCnt = 0;
    int getTimes = 0;
    while(getTimes < 50)
    {
        try {
            vector<drawcard_data> res = drawObj.tenGet();
            getTimes++;
            flush(cout);
            cout << endl;

            for(auto& e : res)
            {
                cout << "���: ";

                cout << "id:\t" << e.m_id << "\t";
                cout << "����:\t" << e.m_name << "\t";
                cout << "ϡ�ж�:\t" << e.m_quality << "\t";
                cout << "����:\t" << e.m_pro << endl;
                quality_count[e.m_quality]++;


                total_getCnt++;
            }
        }
        catch (exception e){
            cerr << e.what();
            system("pause");
        }
    }

    cout << "ʮ���鿨����:\t" << getTimes << "\t�ܳ鿨����:\t" << total_getCnt << endl;
    for(int i = 1;i < quality_count.size();i++)
    {
        float precise = (float)quality_count[i]/total_getCnt * 100;
        cout << "ϡ�ж�:\t" << i << "\t����:\t" << quality_count[i] << "\t���и���ռ��:\t" << precise << "%" ;
        cout << endl;
    }

    size_t game_money = getTimes * TEN_COAST;
    size_t cost_times = game_money / 12000;
    size_t total_cost = cost_times * 648;

    cout << "��648�������:\t" << cost_times << "\t���������:\t" << total_cost << endl;




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