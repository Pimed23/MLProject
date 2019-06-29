all: main

main: main.o
	g++ -o main main.o -pthread

Thread.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f main *.o