#include "TextQuery.h"
#include <sstream>

using namespace std;

TextQuery::TextQuery(ifstream& infile)
    :m_file(new vector<string>)
{
    string line;
    int i = 0;
    while(getline(infile,line))
    {
        m_file->push_back(line);
        string tempLine = line;

        for(auto& e : tempLine)
        {
            if(e == '.' || e == ',')
                e = ' ';
        }
        istringstream linestream(tempLine);

        string word;

        while(linestream >> word)
        {
            auto& lines = m_wm[word];
            if(!lines)
            {
                lines.reset(new set<line_no>);
            }
            lines->insert(i);
        }
        i++;
    }
}

ResultQuery TextQuery::query(string target)
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);

    if(m_wm.find(target) == m_wm.end())
    {
        return ResultQuery(target,nodata,m_file);
    }
    else
    {
        return ResultQuery(target,m_wm[target],m_file);
    }
}

ostream& printQueryRes(ostream& os,ResultQuery& res)
{
    if(!res.m_linenoPtr)
    {
        os << "该单词" << res.m_target << "未出现在文本文件中!!!" << endl;
        return os;
    }
    os << "查询目标单词: " << res.m_target << "出现的行数--> " << res.m_linenoPtr->size() << "\n";

    for(auto iter = res.m_linenoPtr->begin();iter != res.m_linenoPtr->end();iter++)
    {
        printf("line(%d): ",*iter+1);
        os << (*res.m_linesPtr)[*iter] << endl;
    }
    return os;
}