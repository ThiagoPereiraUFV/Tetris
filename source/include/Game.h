#ifndef GAME_H
#define GAME_H

#include <GL/glut.h>
#include <unistd.h>
#include <cstdlib>
#include <unordered_map>
#include <vector>

#include "Menu.h"
#include "Play.h"

// -------- Tamanho inicial da janela --------

#define WINDOW_WIDTH 500   //	Largura inicial
#define WINDOW_HEIGHT 600  //	Altura inicial

class Game {
   private:
      Menu menu;
      Play play;
      int state = 0;  //   0 - menu, 1 - jogo, 2 - derrota e qualquer outro encerramento do jogo
      int selec = 0;  //   0 a 12 representam o botao esta selecionado
      bool gameRunning = 0;  //  0 - nao, 1 - sim
      GLfloat view_w = WINDOW_WIDTH/2, view_h = WINDOW_HEIGHT/2;  //  Os valores representam a metade do tamanho atual da janela
      pair<GLfloat, GLfloat> p0;  //	Ponto inferior esquerdo retangulo do menu
      pair<GLfloat, GLfloat> p1;  //   Ponto superior direito retangulo do menu
      unordered_map<string, bool> option; // Map usado para determinar a opcao selecionada que ira configurar o jogo
      unordered_map<string, pair<int, bool>> selecN;  // Map usado para mapear o nome do botao ao seu numero e se esta selecionado
      unordered_map<int, string> selecI;  //  Map usado para mapear o numero do botao ao nome
      unordered_map<string, pair<GLfloat, GLfloat>> boxPos; //	Map usado para determinar a posicao dos botoes no menu
      vector<string> optNames;   //  Vetor com o nome dos botoes, NORMAL1 e NORMAL2 sao excecoes pois causam conflito ao usar um map
      unordered_map<string, unordered_map<string, vector<GLfloat>>> colors;   //	Map usado para representar o esquema de cores selecionado
      string cor; //	String que define qual esquema de cores foi selecionado
      char idPecaAtual, ultimaTecla;	//	Auxiliares
   public:
      Game(int argc, char** argv);
      void init();
      void display();
      void updateVariables();
      void reshape(const GLsizei w, const GLsizei h);
      void SpecialKeys(const int key, const int x, const int y);
      void HandleKeyboard(const unsigned char key, const int x, const int y);
      void HandleMouse(const int button, const int btnState, const int x, const int y);
      void MousePassiveMotion(const int x, const int y);
};

#endif