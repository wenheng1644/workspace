//
// Created by нд╨Ц on 2022/1/29.
//

#ifndef CPP_MEMORY_DRAM_TEST_H
#define CPP_MEMORY_DRAM_TEST_H

class A
{
public:
    A() {}
    virtual ~A() {}
};

class B : public A
{
public:
    B() {}
    virtual ~B(){}
};

class C: public B
{
public:
    C() {}
    virtual ~C() {}
};

class D : public B, public A
{
public:
    D() {}
    virtual ~D() {}
};

#endif //CPP_MEMORY_DRAM_TEST_H
