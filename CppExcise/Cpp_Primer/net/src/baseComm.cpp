#include "baseComm.h"

std::vector<std::string> baseComm::strComm::splitWord(const std::string& line)
{
    std::vector<std::string> res;
    if(line.empty())
        return res;

    int fristIndex = -1;
    int endIndex = -1;
    
    for(int i = 0; i < line.size(); i++)
    {
        if(std::isalpha(line[i]))
        {
            if(fristIndex == -1)
                fristIndex = i;

            if(i == line.size() - 1 && fristIndex != -1 && endIndex == -1) 
                endIndex = i;
        }
        else
        {
            if(fristIndex != -1 && endIndex == -1)
                endIndex = i - 1;
        }

        //已经找到子字符串了
        if(fristIndex != -1 && endIndex != -1)
        {
            std::string sub(line, fristIndex, endIndex - fristIndex +1);
            fristIndex = endIndex = -1; //重置标记
            res.push_back(sub);
        }
    }

    return res;
}