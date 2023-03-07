//
// Created by wenheng on 22-10-14.
//

#include "Operator.h"
#include <iostream>
#include <exception>
AbstractOp::AbstractOp() : num1(0), num2(0), status(false) {

}

void AbstractOp::getNumber() {
    double a, b;

    std::cin >> a >> b;

    num1 = a;
    num2 = b;
    status = true;
}


double operatorADD::result() {

    if(status)
        return num2 + num1;
}

operatorADD::operatorADD() : AbstractOp(){

}


operatorMul::operatorMul() : AbstractOp(){

}

double operatorMul::result() {
    return num2 * num1;
}

void operatorDev::getNumber() {
    AbstractOp::getNumber();

    if(num2 != 0) return;

    std::cout << "please input data again" << std::endl;
    while(std::cin >> num1 >> num2)
    {
        if(num2 != 0) break;
        std::cout << "please input data again" << std::endl;
    }

}

operatorDev::operatorDev() : AbstractOp(){

}

double operatorDev::result() {
    return num1 / num2;
}
