.PHONY: all clean

all: main

main: main.o sokoban.o
	g++ -o main main.o sokoban.o

sokoban.o: sokoban.cpp
	g++ -c sokoban.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f main *.o
