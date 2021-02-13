optFlags = -Ofast -std=c++11 -Wall -Werror
extraFlags = -c $(optFlags)
oglFlags = $(optFlags) -lglut -lGL -lGLU
ncursesFlags = $(extraFlags) -lncurses
includePath = ./source/include

Tetris: Game.o
	g++ ./source/main.cpp ./bin/*.o $(oglFlags) -o tetris.out

Menu.o:
	g++ $(includePath)/Menu.cpp $(extraFlags) -o ./bin/Menu.o

Tetris.o:
	g++ $(includePath)/Tetris.cpp $(ncursesFlags) -o ./bin/Tetris.o

Play.o: Tetris.o
	g++ $(includePath)/Play.cpp $(extraFlags) -o ./bin/Play.o

Game.o: Menu.o Play.o
	g++ $(includePath)/Game.cpp $(extraFlags) -o ./bin/Game.o

start:
	./tetris.out

clean:
	rm ./bin/*.o *.out