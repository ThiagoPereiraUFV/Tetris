#ifndef MENU_H
#define MENU_H

#include <GL/glut.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Menu {
	private:
		string cor;	//	Selected color scheme
		GLfloat sxmenu, symenu;	//	X and Y text scale
		GLfloat view_w, view_h;	//	Half of game window width and height size
		pair<GLfloat, GLfloat> p0, p1;	//	Bottom left and top right menu rectangle points
		unordered_map<string, pair<GLfloat, GLfloat>> boxPos;	//	Menu buttons position
		unordered_map<string, unordered_map<string, vector<GLfloat>>> colors;   //	Color scheme
		unordered_map<string, bool> option;	//	Options selected to set up a new game
		unordered_map<string, pair<int, bool>> selecN;	//	Map button to its id and if its selected
		const vector<string> optNames{
			"INICIAR", "NORMAL1", "RAPIDO",
			"TURBO", "20x10", "30x15",
			"50x25", "Cores1", "Cores2",
			"Cores3", "NORMAL2", "BEBADO", "SAIR"
		};	//  Button names
	public:
		Menu();
		Menu(
			const unordered_map<string, unordered_map<string, vector<GLfloat>>> &colors,
			const string &cor, const unordered_map<string, bool> &option,
			const unordered_map<string, pair<int, bool>> &selecN,
			const GLfloat &view_w, const GLfloat &view_h);
		~Menu();
		Menu &operator=(const Menu *o);
		string mousePointer(const GLint x, const GLint y);
		void drawText(const GLint x, const GLint y, const GLfloat sx, const GLfloat sy, const string text);
		void drawButton(const pair<GLfloat, GLfloat> &pos, const string text);
		void renderMenu();
};

#endif