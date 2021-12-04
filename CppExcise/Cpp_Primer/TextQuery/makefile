TextQ:TextQueryWithClass.o TextQuery.o
	g++ -o TextQ TextQueryWithClass.o TextQuery.o
TextQueryWithClass.o:TextQueryWithClass.cpp TextQuery.h ResultQuery.h
	g++ -c TextQueryWithClass.cpp
TextQuery.o:TextQuery.cpp TextQuery.h ResultQuery.h
	g++ -c TextQuery.cpp

clean:
	rm -rf *.o TextQ
