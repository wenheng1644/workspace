//
// Created by нд╨Ц on 2022/10/3.
//

#ifndef WIN_CLIENT_CHAT_WIN_CLIENT_CHAT_H
#define WIN_CLIENT_CHAT_WIN_CLIENT_CHAT_H

#include "windows.h"
#include "winsock2.h"
#include "process.h"
#include "iostream"
#include "cstring"

unsigned handle_puts(void * args);
unsigned handle_read(void * args);
void __main_client();

#endif //WIN_CLIENT_CHAT_WIN_CLIENT_CHAT_H
