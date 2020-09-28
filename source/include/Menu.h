#ifndef MENU_H
#define MENU_H

#include <GL/glut.h>
#include <string>

class Menu {
	private:
	public:
		string mousePointer(const GLint x, const GLint y);
		void drawText(const GLint x, const GLint y, const GLfloat sx, const GLfloat sy, const string text);
		void drawButton(const pair<GLfloat, GLfloat> &pos, const string text);
		void renderMenu();
};

#endif