#include "chatRoom.h"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cout << "argc number not equal = 2" << std::endl;
        return 0; 
    }

    const char* ip = argv[1];
    u_short port = std::stoi(std::string(argv[2]));

    std::cout << "ip = " << ip << "\tport = " << port << std::endl;
    chatRoom room(ip, port);

    room.start();
    return 0;
}