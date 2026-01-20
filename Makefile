main: main.o game.o
	g++ -std=c++14 main.o game.o -o main
main.o: main.cc
	g++ -std=c++14 -c main.cc
game.o: game.cc game.h
	g++ -std=c++14 -c game.cc
clean:
	rm *.o main
.PHONY: clean