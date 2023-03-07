//
// Created by wenheng on 22-10-17.
//

#include "templateMode.h"
#include <iostream>
void templateMode::dailyPrint() {
    std::cout << "早上 = " << std::endl;
    monring();
    std::cout << "下午 = " << std::endl;
    afternoon();
    std::cout << "晚上 = " << std::endl;
    evening();
    std::cout << "午夜 = " << std::endl;
    moonNight();
}

void templateMode::moonNight() {
    std::cout << "moonNight = " << " 11:30 go to sleep " << std::endl;
}

void weizhen::monring()
{
    std::cout << "weizhen: maybe eat someting" << std::endl;
}

void weizhen::afternoon() {
    std::cout << "weizhen: read some book" << std::endl;
}

void weizhen::evening() {
    std::cout << "weizhen: read some book maybe" << std::endl;
}

weizhen::weizhen()  : templateMode(){

}

other::other() : templateMode(){

}

void other::monring() {
    std::cout << "other still to sleep" << std::endl;
}

void other::afternoon() {
    std::cout << "other go to play game" << std::endl;
}

void other::evening() {
    std::cout << "other still play game" << std::endl;
}
