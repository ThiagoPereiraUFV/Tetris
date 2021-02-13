#ifndef PLAY_H
#define PLAY_H

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

#include "Tetris.h"

class Play {
	private:
		static int state;	//	0 - menu, 1 - setting up game, 2 - game, 3 - game over and 4 - game exit
		static GLfloat spin;	//	Define table rotation on Bebado mode
		static string color;	//	Define which color is being used in game
		static pair<int, int> tableSize;	//	Define table size
		static GLfloat view_w, view_h;	//  Half of game window width and height size
		static char pieceId, lastKey;	//	Aux
		static const vector<GLint> rotations;	//	Define available piece rotations
		static Tetris gameStatic, gameDynamic;	//	Define two Tetris objects
		static int speed, height, score;	//	Define game speed, height and score
		static int width, maxHeight, pieceHeight, piecePosition, pieceRotation;	//	Aux
		static unordered_map<string, bool> option;	//	Options selected to set up a new game
		static unordered_map<string, unordered_map<string, vector<GLfloat>>> colors;   //	Color scheme
	public:
		static void setup(
			const unordered_map<string, unordered_map<string, vector<GLfloat>>>&,
			const string&,
			const unordered_map<string, bool>&
		);
		static int getState() { return Play::state; }
		static void setState(const int state) { Play::state = state; }
		static void setLastKey(const char lastKey) { Play::lastKey = lastKey; }
		static void spinDisplay(const int);
		static void drawTable();
		static void renderGameFrame();
		static void drawSquare(const GLint, const GLint, const char);
		static void setView(const GLfloat&, const GLfloat&);
		static void drawText(const pair<GLfloat, GLfloat>&, const pair<GLfloat, GLfloat>&, const string);
};

#endif