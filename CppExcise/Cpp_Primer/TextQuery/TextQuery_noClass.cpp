//************************
//tagret    : 该程序是用于对文本文件进行查询某些单词出现位置以及出现个数
//date      : 2021.11.7
//************************ 


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

void PrintResult(vector<string>& lines,
                map<string,set<uint>>& records,
                map<string,uint>& strCount);

int main(int argc,char* argv[])
{
    printf("参数出现次数: %d\n",argc);
    if(argc < 3)
    {   
        cout << "输入参数过少" << endl;
        return -1;
    }
    string strFile(argv[1]);
    ifstream inFile(strFile);

    set<string> targets;

    for(int i = 2; i < argc;i++)
    {
        targets.insert(string(argv[i]));
    }

    if(!inFile)
    {
        cout << "该文件不存在!!!" << endl;
        return -1;
    }
    string line;
    vector<string> lines;
    map<string,set<uint>> m_records;
    map<string,uint> m_strCount;

    int i = 0;
    while(getline(inFile,line))
    {
        lines.push_back(line);
        string temp_line = line;

        for(auto& e : temp_line)
        {
            if(e == '.' || e == ',')
                e = ' ';
        }

        istringstream strStream(temp_line);

        string temp;

        while(strStream >> temp)
        {
            if(temp.empty())
                break;

            if(targets.count(temp))
            {
                if(!m_records.count(temp))
                {
                    set<uint> hashSet;
                    m_records[temp] = hashSet;   
                }
                m_records[temp].insert(i);
                m_strCount[temp]++;
            }
        
        }
        i++;

    }
    PrintResult(lines,m_records,m_strCount);

    return 0;
}

void PrintResult(vector<string>& lines,
                map<string,set<uint>>& records,
                map<string,uint>& strCount)
{
    bool isExist = false;
    for(auto iter = strCount.begin(); iter != strCount.end(); iter++)
    {
        cout << "该单词出现次数为" << iter->second << ": " << iter->first << endl;
        if(iter->second == 0) continue;

        isExist = true;
        cout << iter->first << ": ";
        for(auto& i : records[iter->first])
        {
            cout << lines[i];
        }
        printf("\n");

    }
    if(!isExist)
        printf("所查询的所有单词均未出现...\n");
    printf("Done...");
}

