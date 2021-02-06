oglFlags = -O3 -lglut -lGL -lGLU
ncursesFlags = -O3 -lncurses
extraFlags = -c -O3
includePath = ./source/include

Tetris: Menu.o Tetris.o Play.o Game.o
	g++ ./source/main.cpp ./bin/*.o $(oglFlags) -o tetris.out

Menu.o:
	g++ $(includePath)/Menu.cpp $(extraFlags) -o ./bin/Menu.o

Tetris.o:
	g++ $(includePath)/Tetris.cpp $(extraFlags) -o ./bin/Tetris.o

Play.o:
	g++ $(includePath)/Play.cpp $(extraFlags) -o ./bin/Play.o

Game.o:
	g++ $(includePath)/Game.cpp $(extraFlags) -o ./bin/Game.o

start:
	./tetris.out && clear

clear:
	rm ./bin/*.o *.out