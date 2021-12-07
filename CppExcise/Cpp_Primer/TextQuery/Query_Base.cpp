#include "Query_Base.h"
#include <algorithm>

inline
Query::Query(const std::string& textStr) : q(new WordQuery(textStr))
{

}

inline
Query operator~(const Query& operand)
{
    return std::shared_ptr<Query_Base>(new NotQuery(operand));
}

inline
Query operator&(const Query& left,const Query& right)
{
    return std::shared_ptr<Query_Base>(new AndQuery(left,right));
}

inline
Query operator|(const Query& left,const Query& right)
{
    return std::shared_ptr<Query_Base>(new OrQuery(left,right));
}

Query::Query(const std::string& textStr) : q(new WordQuery(textStr))
{

}

ResultQuery OrQuery::eval(const TextQuery& theTextQuery)
{
    ResultQuery left = lhs.eval(theTextQuery);
    ResultQuery right = rhs.eval(theTextQuery);

    auto lines_no = make_shared<set<size_t>>(left.begin(),left.end());

    lines_no->insert(right.begin(),right.end());

    return ResultQuery(rep(),lines_no,left.get_file());
}

ResultQuery AndQuery::eval(const TextQuery& theTextQuery)
{
    ResultQuery left = lhs.eval(theTextQuery);
    ResultQuery right = rhs.eval(theTextQuery);

    shared_ptr<set<size_t>> lines_no = make_shared<set<size_t>>();

    std::set_intersection(left.begin(),left.end(),
                            right.begin(),right.end(),
                            inserter(*lines_no,lines_no->begin()));    
}

ResultQuery NotQuery::eval(const TextQuery& theTextQuery)
{
    ResultQuery res = query.eval(theTextQuery);

    auto ptr = res.begin();

    auto ans = make_shared<set<size_t>>();

    int cnt = res.get_file()->size();

    for(int i = 0; i < cnt; i++)
    {
        if(ptr == res.end() || *ptr != i)
            ans->insert(i);
        else if(ptr != res.end())
            ptr++;        
    }

    return ResultQuery(query.rep(),ans,res.get_file());
}