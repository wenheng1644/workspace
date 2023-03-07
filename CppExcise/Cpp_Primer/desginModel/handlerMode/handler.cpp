//
// Created by wenheng on 22-10-18.
//

#include "handler.h"

void handler::setPreHandler(handler *h) {
    m_preHandler = h;
}

void banZhang::handleRequest(int req) {
    if(req != 0)
    {
        m_preHandler->handleRequest(req);
        return;
    }
    std::cout << "banZhang handle it = " << req << std::endl;
}

void laoShi::handleRequest(int req) {
    if(req > 2)
    {
        m_preHandler->handleRequest(req);
        return;
    }
    std::cout << "laoshi handle it = " << req << std::endl;
}

void xiaoZhang::handleRequest(int req) {
//    if(req != 0)
//    {
//        m_preHandler->handleRequest(req);
//        return;
//    }
    std::cout << "xiaozhang handle it = " << req << std::endl;
}
