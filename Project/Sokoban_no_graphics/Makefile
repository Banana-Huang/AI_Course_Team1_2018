.PHONY: all clean

all: main

main: clean main.o sokoban.o agent.o
	g++ -o main main.o sokoban.o agent.o

sokoban.o: sokoban.cpp
	g++ -c sokoban.cpp

agent.o: agent.cpp
	g++ -c agent.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f main *.o
