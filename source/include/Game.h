#ifndef GAME_H
#define GAME_H

#include <GL/glut.h>
#include <unistd.h>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <functional>
#include "Menu.h"
#include "Play.h"

// -------- Initial window size --------

#define WINDOW_WIDTH 500	//	Width
#define WINDOW_HEIGHT 600	//	Height

class Game {
	private:
		static int state;	//	0 - menu, 1 - setting up game, 2 - game, 3 - game over and 4 - game exit
		static int selec;	//	0 to 12 represents current selected button
		static string color;	//	Define which color is being used in game
		static GLfloat view_w, view_h;	//  Half of game window width and height size
		static unordered_map<string, bool> option;	//	Options selected to set up a new game
		static unordered_map<string, pair<int, bool>> selecN;	//	Map button to its id and if its selected
		static unordered_map<int, string> selecI;	//  Map button id to its name
		static unordered_map<string, unordered_map<string, vector<GLfloat>>> colors;   //	Color scheme
	public:
		static void game(int argc, char** argv);
		static void init();
		static void display();
		static void updateColors();
		static void reshape(const GLsizei w, const GLsizei h);
		static void SpecialKeys(const int key, const int x, const int y);
		static void HandleKeyboard(const unsigned char key, const int x, const int y);
		static void HandleMouse(const int button, const int btnState, const int x, const int y);
		static void MousePassiveMotion(const int x, const int y);
};

#endif