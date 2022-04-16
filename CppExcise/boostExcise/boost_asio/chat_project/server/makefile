
chatServer:main.o chatMsg.o chatRoom.o chatServer.o chatSession.o dateTimeMgr.o
        g++ main.o chatMsg.o chatRoom.o chatServer.o chatSession.o dateTimeMgr.o -o chatServer -lpthread

main.o:main.cpp
        g++ main.cpp -c -o main.o

chatMsg.o:chatMsg.cpp
        g++ chatMsg.cpp -c -o chatMsg.o

chatRoom.o:chatRoom.cpp
        g++ chatRoom.cpp -c -o chatRoom.o

chatServer.o:chatServer.cpp
        g++ chatServer.cpp -c -o chatServer.o

chatSession.o:chatSession.cpp
        g++ chatSession.cpp -c -o chatSession.o

dateTimeMgr.o:dateTimeMgr.cpp
        g++ dateTimeMgr.cpp -c -o dateTimeMgr.o

clean:
        rm -rf *.o chatServer
