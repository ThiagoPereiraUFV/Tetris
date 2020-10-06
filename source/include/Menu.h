#ifndef MENU_H
#define MENU_H

#include <GL/glut.h>
#include <string>
#include <vector>
#include <unordered_map>

class Menu {
	private:
		vector<string> optNames;	//  Vetor com o nome dos botoes, NORMAL1 e NORMAL2 sao excecoes pois causam conflito ao usar um map
		pair<GLfloat, GLfloat> p0;	//	Ponto inferior esquerdo retangulo do menu
		pair<GLfloat, GLfloat> p1;	//	Ponto superior direito retangulo do menu
		unordered_map<string, pair<GLfloat, GLfloat>> boxPos;	//	Map usado para determinar a posicao dos botoes no menu
		unordered_map<string, unordered_map<string, vector<GLfloat>>> colors;	//	Map usado para representar o esquema de cores selecionado
		string cor;	//	String que define qual esquema de cores foi selecionado
		unordered_map<string, bool> option;	//	Map usado para determinar a opcao selecionada que ira configurar o jogo
		unordered_map<string, pair<int, bool>> selecN;	// Map usado para mapear o nome do botao ao seu numero e se esta selecionado
		GLfloat view_w, view_h;	//  Os valores representam a metade do tamanho atual da janela
		GLfloat sxmenu, symenu;	//	Escala do texto do menu em x e y
	public:
		string mousePointer(const GLint x, const GLint y);
		void drawText(const GLint x, const GLint y, const GLfloat sx, const GLfloat sy, const string text);
		void drawButton(const pair<GLfloat, GLfloat> &pos, const string text);
		void renderMenu();
};

#endif