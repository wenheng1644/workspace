#include "ResultQuery.h"
#include "TextQuery.h"

int main(int argc,char* argv[])
{
    if(argc < 3)
    {
        cout << "输入参数过少.........." << endl;
        return -1;   
    }

    string strFile(argv[1]);
    ifstream inFile(strFile);

    if(!inFile)
    {
        cout << "该文件不存在.........." << endl;
        return -1;
    }
    TextQuery TextQueryObj(inFile);
    vector<string> Texts;
    for(int i = 2;i < argc;i++)
    {
        Texts.push_back(string(argv[i]));
    }

    for(auto& e : Texts)
    {
        ResultQuery res = TextQueryObj.query(e);
        printQueryRes(cout,res);
    }

    return 0;
}