#ifndef QUERY_BASE
#define QUERY_BASE
#include "TextQuery.h"
//查询继承体系中的抽象基类（处于顶端）
class Query;
class Query_Base
{
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_Base() = default;

private:
    virtual ResultQuery eval(const TextQuery& theTxtQuery) const = 0;
    virtual std::string rep() const = 0;
};

class WordQuery;
class Query
{
    friend Query operator~(const Query& theQuery);
    friend Query operator|(const Query& theQuery1,const Query& theQuery2);
    friend Query operator&(const Query& theQuery1,const Query& theQuery2);


public:
    Query(const std::string& textStr);
    ResultQuery eval(const TextQuery &t) const override { return q->eval(t);}

    std::string rep() const override { return q->rep();}

private:
    Query(std::shared_ptr<Query_Base> query) : q(query) {}
    std::shared_ptr<Query_Base> q;
};

class WordQuery : public Query_Base
{
    friend class Query;
    WordQuery(const std::string& s) : query_word(s) {}
    ResultQuery eval(TextQuery& theTxtQuery) const { return theTxtQuery.query(query_word);}

    std::string rep() const { return query_word;}
    std::string query_word;
};

class NotQuery : public Query_Base
{
    friend Query operator~(const Query& q);
    NotQuery(const Query& q) : query(q) {}
    std::string rep() const { return "~(" + query.rep() + ")";}
    ResultQuery eval(const TextQuery& theTextQuery) const;
    Query query;
};

class BinaryQuery : public Query_Base
{
protected:
    BinaryQuery(const Query& l,const Query& r,std::string& s)
        :lhs(l),rhs(r),opSym(s) {}

    std::string rep() const { return "(" + lhs.rep() + " " \
                                    opSym + " " +rhs.rep() + ")";}

    Query lhs,rhs;
    std::string opSym;
};

class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query& l,const Query& r);
    AndQuery(const Query& left,const Query& right) : BinaryQuery(left,right,"&") {}
    ResultQuery eval(const TextQuery& theTextQuery) const;
};

class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query& left,const Query& right);
    OrQuery(const Query& left,const Query& right) : BinaryQuery(left,right,"|") {}
    ResultQuery eval(const TextQuery& theTextQuery) const;
};
#endif