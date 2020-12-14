#ifndef GAME_H
#define GAME_H

#include <GL/glut.h>
#include <unistd.h>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <functional>

using namespace std;

// -------- Tamanho inicial da janela --------

#define WINDOW_WIDTH 500   //	Largura inicial
#define WINDOW_HEIGHT 600  //	Altura inicial

#include "Menu.h"
#include "Play.h"

class Game {
	private:
		static Menu menu;  // Menu object
		static Play play;  // Tetris game object
		static int state;  //   0 - menu, 1 - jogo, 2 - derrota e qualquer outro encerramento do jogo
		static int selec;  //   0 a 12 representam o botao esta selecionado
		static bool gameRunning;  //  0 - nao, 1 - sim
		static string cor;	//	String que define qual esquema de cores foi selecionado
		static char ultimaTecla;	//	Auxiliares
		static GLfloat view_w, view_h;  //  Os valores representam a metade do tamanho atual da janela
		static pair<GLfloat, GLfloat> p0;  //	Ponto inferior esquerdo retangulo do menu
		static pair<GLfloat, GLfloat> p1;  //   Ponto superior direito retangulo do menu
		static unordered_map<string, bool> option; // Map usado para determinar a opcao selecionada que ira configurar o jogo
		static unordered_map<string, pair<int, bool>> selecN;  // Map usado para mapear o nome do botao ao seu numero e se esta selecionado
		static unordered_map<int, string> selecI;  //  Map usado para mapear o numero do botao ao nome
		static unordered_map<string, unordered_map<string, vector<GLfloat>>> colors;   //	Map usado para representar o esquema de cores selecionado
	public:
		static void game(int argc, char** argv);
		static void init();
		static void display();
		static void updateVariables();
		static void reshape(const GLsizei w, const GLsizei h);
		static void SpecialKeys(const int key, const int x, const int y);
		static void HandleKeyboard(const unsigned char key, const int x, const int y);
		static void HandleMouse(const int button, const int btnState, const int x, const int y);
		static void MousePassiveMotion(const int x, const int y);
};

#endif