#ifndef PLAY_H
#define PLAY_H

#include <GL/glut.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "Tetris.h"

class Play {
   private:
		int state;  //   0 - menu, 1 - jogo, 2 - derrota e qualquer outro encerramento do jogo
      bool gameRunning;  //  0 - nao, 1 - sim
      GLfloat spin = 0.0;  //	Define a rotacao do tabuleiro durante o modo bebado
      pair<int, int> tam;	//	Define o tamanho do tabuleiro
      int vel, altura, alturaOld, pontos;	//	Define a velocidade, altura, altura anterior e pontos respectivamente
      Tetris jogo(), jogoComPecaCaindo();	//	Define dois objetos do Tetris
      const vector<GLint> possiveisRotacoes{0, 90, 180, 270};	//	Define as rotacoes disponiveis
      int larguraJogo, alturaMaximaJogo, alturaPecaAtual, posicaoPecaAtual, rotacaoPecaAtual;	//	Auxiliares
      char idPecaAtual, ultimaTecla;	//	Auxiliares
      unordered_map<string, unordered_map<string, vector<GLfloat>>> colors;	//	Map usado para representar o esquema de cores selecionado
		pair<GLfloat, GLfloat> p0;	//	Ponto inferior esquerdo retangulo do menu
		pair<GLfloat, GLfloat> p1;	//	Ponto superior direito retangulo do menu
		string cor;	//	String que define qual esquema de cores foi selecionado
		unordered_map<string, bool> option;	//	Map usado para determinar a opcao selecionada que ira configurar o jogo
		unordered_map<string, pair<int, bool>> selecN;	// Map usado para mapear o nome do botao ao seu numero e se esta selecionado
		GLfloat view_w, view_h;	//  Os valores representam a metade do tamanho atual da janela
   public:
      Play();
      Play(
         const unordered_map<string, unordered_map<string, vector<GLfloat>>> &colors,
         const pair<GLfloat, GLfloat> &p0, const pair<GLfloat, GLfloat> &p1,
         const string &cor, const unordered_map<string, bool> &option,
         const GLfloat &view_w, const GLfloat &view_h,
		   const int &state, const bool &gameRunning);
      void spinDisplay(const int x);
      void exibeObjeto(const GLint x, const GLint y, const char c);
      void exibeJogo();
      void renderGameFrame();
      void configGame();
      void configVars();
};

#endif