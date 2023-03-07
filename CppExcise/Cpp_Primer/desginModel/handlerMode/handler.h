//
// Created by wenheng on 22-10-18.
//

#ifndef HANDLERMODE_HANDLER_H
#define HANDLERMODE_HANDLER_H

#include <iostream>

class handler {
public:
    handler() = default;
    virtual ~handler() = default;

    void setPreHandler(handler* h);
    virtual void handleRequest(int req) = 0;
protected:
    handler* m_preHandler;

    enum Req{
        shangcisuo  = 0,
        yanchijiaozuoye,
        qingjia,
        tuixue,
    };
};

class banZhang : public handler
{
public:
    banZhang() = default;
    ~banZhang() = default;
    void handleRequest(int req) override;
};


class laoShi : public  handler
{
public:
    laoShi() = default;
    ~laoShi() = default;
    void handleRequest(int req) override;

};

class xiaoZhang : public handler
{
public:
    xiaoZhang() = default;
    ~xiaoZhang() = default;

    void handleRequest(int req) override;
};



#endif //HANDLERMODE_HANDLER_H
