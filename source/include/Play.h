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
		int state;  //   0 - menu, 1 - jogo, 2 - derrota e qualquer outro encerramento do jogo
		bool gameRunning;  //  0 - nao, 1 - sim
		GLfloat spin;  //	Define a rotacao do tabuleiro durante o modo bebado
		pair<int, int> tam;	//	Define o tamanho do tabuleiro
		int vel, altura, alturaOld, pontos;	//	Define a velocidade, altura, altura anterior e pontos respectivamente
		Tetris jogo, jogoComPecaCaindo;	//	Define dois objetos do Tetris
		const vector<GLint> possiveisRotacoes{0, 90, 180, 270};	//	Define as rotacoes disponiveis
		int larguraJogo, alturaMaximaJogo, alturaPecaAtual, posicaoPecaAtual, rotacaoPecaAtual;	//	Auxiliares
		char idPecaAtual, ultimaTecla;	//	Auxiliares
		unordered_map<string, unordered_map<string, vector<GLfloat>>> colors;	//	Map usado para representar o esquema de cores selecionado
		pair<GLfloat, GLfloat> p0, p1;	//	Ponto inferior esquerdo retangulo e superior direito retangulo do menu
		string cor;	//	String que define qual esquema de cores foi selecionado
		unordered_map<string, bool> option;	//	Map usado para determinar a opcao selecionada que ira configurar o jogo
		GLfloat view_w, view_h;	//  Os valores representam a metade do tamanho atual da janela
	public:
		Play();
		Play(
			const unordered_map<string, unordered_map<string, vector<GLfloat>>> &colors,
			const string &cor, const unordered_map<string, bool> &option,
			const GLfloat &view_w, const GLfloat &view_h,
			const int &state, const bool &gameRunning);
		~Play();
		Play &operator=(const Play *o);
		void spinDisplay(const int x);
		void exibeObjeto(const GLint x, const GLint y, const char c);
		void exibeJogo();
		void renderGameFrame();
		void setUltimaTecla(const char ultimaTecla) { this->ultimaTecla = ultimaTecla; }
		void configGame();
		void configVars();
		void drawText(const GLint x, const GLint y, const GLfloat sx, const GLfloat sy, const string text);
};

#endif