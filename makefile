jogo.o : source/main.cpp
	g++  source/main.cpp source/Tetris.cpp -lglut -lGL -lGLU -lm -std=c++11 -lncurses -o main.out && ./main.out