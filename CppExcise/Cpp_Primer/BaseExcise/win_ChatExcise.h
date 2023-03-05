//
// Created by 文恒 on 2022/10/2.
//

#ifndef BASEEXCISE_WIN_CHATEXCISE_H
#define BASEEXCISE_WIN_CHATEXCISE_H

#include "windows.h"
#include "process.h"
#include "iostream"
#include "winsock2.h"


const int CLIENT_MAX = 20;
const int STRLEN_MAX = 50;


//服务端代码
unsigned handle_client(void * arg);
void sendMsg(char msgs[], int bytes);

void __main_server();



#endif //BASEEXCISE_WIN_CHATEXCISE_H
