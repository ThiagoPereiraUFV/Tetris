jogo.o : main.cpp
	g++  main.cpp Tetris.cpp -lglut -lGL -lGLU -lm -std=c++11 -lncurses -o main.out && ./main.out