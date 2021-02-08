#ifndef MENU_H
#define MENU_H

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>

using namespace std;

class Menu {
	private:
		static string color;	//	Selected color scheme
		static GLfloat sxmenu, symenu;	//	X and Y text scale
		static GLfloat view_w, view_h;	//	Half of game window width and height size
		static pair<GLfloat, GLfloat> p0, p1;	//	Top right menu and bottom left rectangle points
		static unordered_map<string, pair<GLfloat, GLfloat>> boxPos;	//	Menu buttons position
		static unordered_map<string, unordered_map<string, vector<GLfloat>>> colors;   //	Color scheme
		static unordered_map<string, bool> option;	//	Options selected to set up a new game
		static unordered_map<string, pair<int, bool>> selecN;	//	Map button to its id and if its selected
		static vector<string> optNames;	//  Button names
	public:
		static void setup(
			const unordered_map<string, unordered_map<string, vector<GLfloat>>>&,
			const string&, const unordered_map<string, bool>&,
			const unordered_map<string, pair<int, bool>>&
		);
		static void setView(const GLfloat&, const GLfloat&);
		static string mousePointer(const GLint, const GLint);
		static void drawText(const pair<GLfloat, GLfloat>&, const pair<GLfloat, GLfloat>&, const string);
		static void drawButton(const pair<GLfloat, GLfloat>&, const string);
		static void renderMenu();
};

#endif