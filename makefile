jogo.o : source/main.cpp
	g++  source/main.cpp source/include/Tetris.cpp -O3 -lglut -lGL -lGLU -lm -std=c++11 -lncurses -o main.out && ./main.out