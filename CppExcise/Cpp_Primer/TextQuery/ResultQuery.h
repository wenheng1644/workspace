#ifndef RESULTQUERY
#define RESULTQUERY

#include <vector>
#include <map>
#include <string>
#include <set>
#include <memory>
using namespace std;
class ResultQuery
{
friend ostream& printQueryRes(ostream& os,ResultQuery& res);
public:
    ResultQuery(string target,shared_ptr<set<size_t>> lineno_ptr,shared_ptr<vector<string>> lines_ptr)
        : m_target(target),m_linenoPtr(lineno_ptr),m_linesPtr(lines_ptr) {}
    ~ResultQuery() = default;

    set<size_t>::iterator begin(){
        return m_linenoPtr->begin();
    }

    set<size_t>::iterator end(){
        return m_linenoPtr->end();
    }

    shared_ptr<vector<string>> get_file(){
        return m_linesPtr;
    }

private:
    string m_target;
    shared_ptr<set<size_t>> m_linenoPtr;
    shared_ptr<vector<string>> m_linesPtr;
};



#endif