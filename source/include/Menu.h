#ifndef MENU_H
#define MENU_H

#include <GL/glut.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Menu {
	private:
		string cor;	//	String que define qual esquema de cores foi selecionado
		GLfloat sxmenu, symenu;	//	Escala do texto do menu em x e y
		GLfloat view_w, view_h;	//  Os valores representam a metade do tamanho atual da janela
		pair<GLfloat, GLfloat> p0, p1;	//	Ponto inferior esquerdo retangulo e superior direito retangulo do menu
		unordered_map<string, pair<GLfloat, GLfloat>> boxPos;	//	Map usado para determinar a posicao dos botoes no menu
		unordered_map<string, unordered_map<string, vector<GLfloat>>> colors;	//	Map usado para representar o esquema de cores selecionado
		unordered_map<string, bool> option;	//	Map usado para determinar a opcao selecionada que ira configurar o jogo
		unordered_map<string, pair<int, bool>> selecN;	// Map usado para mapear o nome do botao ao seu numero e se esta selecionado
		const vector<string> optNames{
			"INICIAR", "NORMAL1", "RAPIDO",
			"TURBO", "20x10", "30x15",
			"50x25", "Cores1", "Cores2",
			"Cores3", "NORMAL2", "BEBADO", "SAIR"
		};	//  Vetor com o nome dos botoes, NORMAL1 e NORMAL2 sao excecoes pois causam conflito ao usar um map
	public:
		Menu();
		Menu(
			const unordered_map<string, unordered_map<string, vector<GLfloat>>> &colors,
			const string &cor, const unordered_map<string, bool> &option,
			const unordered_map<string, pair<int, bool>> &selecN,
			const GLfloat &view_w, const GLfloat &view_h);
		Menu &operator=(const Menu *o);
		string mousePointer(const GLint x, const GLint y);
		void drawText(const GLint x, const GLint y, const GLfloat sx, const GLfloat sy, const string text);
		void drawButton(const pair<GLfloat, GLfloat> &pos, const string text);
		void renderMenu();
};

#endif