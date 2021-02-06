#ifndef PLAY_H
#define PLAY_H

#include <GL/glut.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

#include "Tetris.h"

class Play {
	private:
		static int state;  //   0 - menu, 1 - jogo, 2 - derrota e qualquer outro encerramento do jogo
		static GLfloat spin;  //	Define a rotacao do tabuleiro durante o modo bebado
		static pair<int, int> tam;	//	Define o tamanho do tabuleiro
		static int vel, altura, alturaOld, pontos;	//	Define a velocidade, altura, altura anterior e pontos respectivamente
		static Tetris jogo, jogoComPecaCaindo;	//	Define dois objetos do Tetris
		static const vector<GLint> possiveisRotacoes;	//	Define as rotacoes disponiveis
		static int larguraJogo, alturaMaximaJogo, alturaPecaAtual, posicaoPecaAtual, rotacaoPecaAtual;	//	Auxiliares
		static char idPecaAtual, lastKey;	//	Auxiliares
		static unordered_map<string, unordered_map<string, vector<GLfloat>>> colors;	//	Map usado para representar o esquema de cores selecionado
		static string color;	//	String que define qual esquema de cores foi selecionado
		static unordered_map<string, bool> option;	//	Map usado para determinar a opcao selecionada que ira configurar o jogo
		static GLfloat view_w, view_h;	//  Os valores representam a metade do tamanho atual da janela
	public:
		static void setup(
			const unordered_map<string, unordered_map<string, vector<GLfloat>>> &colors,
			const string &color, const unordered_map<string, bool> &option
		);
		static void spinDisplay(const int x);
		static void exibeObjeto(const GLint x, const GLint y, const char c);
		static void exibeJogo();
		static void renderGameFrame();
		static int getState() { return Play::state; }
		static void setState(const int &state) { Play::state = state; }
		static void setUltimaTecla(const char lastKey) { Play::lastKey = lastKey; }
		static void setView(const GLfloat &view_w, const GLfloat &view_h);
		static void configGame();
		static void configVars();
		static void drawText(const GLint x, const GLint y, const GLfloat sx, const GLfloat sy, const string text);
};

#endif