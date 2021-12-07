#ifndef TEXTQUREY
#define TEXTQUREY

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <memory>
#include "ResultQuery.h"

using namespace std;
class ResultQuery;

class TextQuery{
friend ResultQuery;
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream& infie);
    ResultQuery query(string target);
private:
    shared_ptr<vector<string>> m_file;
    map<string,shared_ptr<set<line_no>>> m_wm; 

};

#endif