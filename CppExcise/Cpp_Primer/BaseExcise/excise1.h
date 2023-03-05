//
// Created by нд╨Ц on 2022/7/9.
//

#ifndef BASEEXCISE_EXCISE1_H
#define BASEEXCISE_EXCISE1_H

#define MAXCOL 1000

#include <iostream>
#include "cstring"

int read_colums(int colums[], int col);
void rerange(char * output, const char* input, const int* colums, int cols);


class base{
public:
    base(int v1, int v2, int v3) : a(v1), b(v2), c(v3) {}
    virtual void print_it() { printf("I am base\n");}

    virtual ~base(){}
    int a;
protected:
    int b;
private:
    int c;
};


class drive_public : public  base
{
public:
    drive_public(int v1, int v2, int v3) : base(v1, v2, v3) {}
    void print_it() override { printf("I am drive_public\n");}
};




#endif //BASEEXCISE_EXCISE1_H
