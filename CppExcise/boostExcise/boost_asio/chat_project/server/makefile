
chatServer:main.o chatMsg.o chatRoom.o chatServer.o chatSession.o dateTimeMgr.o
	g++ main.o chatMsg.o chatRoom.o chatServer.o chatSession.o dateTimeMgr.o -o chatServer

main.o:main.cpp
	g++ main.cpp -c main.o

chatMsg.o:chatMsg.cpp
	g++ chatMsg.cpp -c chatMsg.o

chatRoom.o:chatRoom.cpp
	g++ chatRoom.cpp -c chatRoom.o

chatServer.o:chatServer.cpp
	g++ chatServer.cpp -c chatServer.o

chatSession.o:chatSession.cpp
	g++ chatSession.cpp -c chatSession.o

dateTimeMgr.o:dateTimeMgr.cpp
	g++ dateTimeMgr.cpp -c dateTimeMgr.o

clean:
	rm -rf *.o chatServer