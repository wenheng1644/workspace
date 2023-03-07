//
// Created by wenheng on 22-10-17.
//

#ifndef TEMPLATEMODE_TEMPLATEMODE_H
#define TEMPLATEMODE_TEMPLATEMODE_H


class templateMode {
public:
    templateMode() = default;
    ~templateMode() = default;

    void dailyPrint();

protected:
    virtual void monring() = 0;
    virtual void afternoon() = 0;
    virtual void evening() = 0;

    void moonNight();
};

class weizhen : public templateMode
{
public:
    weizhen();
    ~weizhen() = default;

protected:
    void monring() override;
    void afternoon() override;
    void evening() override;
};

class other : public templateMode
{
public:
    other();
    ~other() = default;

protected:
    void monring() override;
    void afternoon() override;
    void evening() override;
};


#endif //TEMPLATEMODE_TEMPLATEMODE_H
