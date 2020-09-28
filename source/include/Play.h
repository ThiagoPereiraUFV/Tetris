#ifndef PLAY_H
#define PLAY_H

#include <GL/glut.h>
#include <vector>

#include "Tetris.h"

class Play {
   private:
      GLfloat spin;  //	Define a rotacao do tabuleiro durante o modo bebado
      pair<int, int> tam;	//	Define o tamanho do tabuleiro
      int vel, altura, alturaOld, pontos;	//	Define a velocidade, altura, altura anterior e pontos respectivamente
      Tetris jogo(), jogoComPecaCaindo();	//	Define dois objetos do Tetris
      const vector<GLint> possiveisRotacoes{0, 90, 180, 270};	//	Define as rotacoes disponiveis
      int larguraJogo, alturaMaximaJogo, alturaPecaAtual, posicaoPecaAtual, rotacaoPecaAtual;	//	Auxiliares
      char idPecaAtual, ultimaTecla;	//	Auxiliares
   public:
      void spinDisplay(const int x);
      void exibeObjeto(const GLint x, const GLint y, const char c);
      void exibeJogo();
      void renderGameFrame();
      void configGame();
      void configVars();
};

#endif