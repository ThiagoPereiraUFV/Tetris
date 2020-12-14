#jogo: source/main.cpp
	#g++  source/main.cpp source/include/Tetris.cpp -O3 -lglut -lGL -lGLU -lm -std=c++11 -lncurses -o main.out && ./main.out

jogo: source/test.cpp
	g++  source/test.cpp source/include/Game.cpp -O3 -lglut -lGL -lGLU -lm -std=c++11 -lncurses -o main.out && ./main.out

all: program

program: test.o Menu.o Play.o
	g++ test.o Menu.o  Play.o -O3 -lglut -lGL -lGLU -lm -std=c++11 -lncurses -o program

test.o: source/test.cpp
	g++ -c source/test.cpp -O3 -lglut -lGL -lGLU -lm -std=c++11

Menu.o: source/include/Menu.cpp
	g++ -c source/include/Menu.cpp -O3 -lglut -lGL -lGLU -lm -std=c++11

Play.o: source/include/Play.cpp source/include/Tetris.cpp
	g++ -c source/include/Play.cpp source/include/Tetris.cpp -O3 -lglut -lGL -lGLU -lm -lncurses -std=c++11

clean:
	rm *.o