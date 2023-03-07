//
// Created by wenheng on 22-10-14.
//

#ifndef FACTORY1_ABSTRACTOP_H
#define FACTORY1_ABSTRACTOP_H


class AbstractOp {

public:
    AbstractOp();
    ~AbstractOp() = default;
    virtual void getNumber();
    virtual double result() = 0;
protected:
    double num1;
    double num2;
    bool status;

};


class operatorADD : public AbstractOp
{
public:
    operatorADD();
    ~operatorADD() = default;
    double result() override;
};

class operatorMul : public AbstractOp
{
public:
    operatorMul();
    ~operatorMul() = default;
    double result() override;
};

class operatorDev : public AbstractOp
{
public:
    operatorDev();
    ~operatorDev() = default;
    void getNumber() override;
    double result() override;
};


#endif //FACTORY1_ABSTRACTOP_H
