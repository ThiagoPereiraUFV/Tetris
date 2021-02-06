#ifndef MENU_H
#define MENU_H

#include <GL/glut.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Menu {
	private:
		static string color;	//	Selected color scheme
		static GLfloat sxmenu, symenu;	//	X and Y text scale
		static GLfloat view_w, view_h;	//	Half of game window width and height size
		static pair<GLfloat, GLfloat> p0, p1;	//	Bottom left and top right menu rectangle points
		static unordered_map<string, pair<GLfloat, GLfloat>> boxPos;	//	Menu buttons position
		static unordered_map<string, unordered_map<string, vector<GLfloat>>> colors;   //	Color scheme
		static unordered_map<string, bool> option;	//	Options selected to set up a new game
		static unordered_map<string, pair<int, bool>> selecN;	//	Map button to its id and if its selected
		static vector<string> optNames;	//  Button names
	public:
		static void setup(
			const unordered_map<string, unordered_map<string, vector<GLfloat>>> &colors,
			const string &color, const unordered_map<string, bool> &option,
			const unordered_map<string, pair<int, bool>> &selecN
		);
		static void setView(const GLfloat &view_w, const GLfloat &view_h);
		static string mousePointer(const GLint x, const GLint y);
		static void drawText(const GLint x, const GLint y, const GLfloat sx, const GLfloat sy, const string text);
		static void drawButton(const pair<GLfloat, GLfloat> &pos, const string text);
		static void renderMenu();
};

#endif