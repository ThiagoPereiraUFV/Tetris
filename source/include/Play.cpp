#include "Play.h"

int Play::state;
GLfloat Play::spin;
string Play::color;
pair<int, int> Play::tableSize;
GLfloat Play::view_w, Play::view_h;
char Play::pieceId, Play::lastKey;
Tetris Play::gameStatic, Play::gameDynamic;
int Play::piecePosition, Play::pieceRotation;
int Play::speed, Play::height, Play::score;
int Play::width, Play::maxHeight, Play::pieceHeight;
unordered_map<string, bool> Play::option;
const vector<GLint> Play::rotations{0, 90, 180, 270};
unordered_map<string, unordered_map<string, vector<GLfloat>>> Play::colors;

//	Set up game color, size and mode
void Play::setup(
		const unordered_map<string, unordered_map<string, vector<GLfloat>>> &colors,
		const string &color, const unordered_map<string, bool> &option
	) {
	spin = 0;
	Play::colors = colors;
	Play::color = color;
	Play::option = option;

	if(Play::option["20x10"]) {
		tableSize = make_pair(20, 10);
		if(Play::option["NORMAL1"])
			speed = 200000;
		else if(Play::option["RAPIDO"])
			speed = 80000;
		else
			speed = 70000;
	} else if(Play::option["30x15"]) {
		tableSize = make_pair(30, 15);
		if(Play::option["NORMAL1"])
			speed = 80000;
		else if(Play::option["RAPIDO"])
			speed = 60000;
		else
			speed = 40000;
	} else {
		tableSize = make_pair(50, 25);
		if(Play::option["NORMAL1"])
			speed = 50000;
		else if(Play::option["RAPIDO"])
			speed = 40000;
		else
			speed = 30000;
	}

	if(Play::option["BEBADO"]) {
		spin = 0.0;
		glutTimerFunc(100, spinDisplay, 0);
	}

	maxHeight = tableSize.first;
	width = tableSize.second;
	gameStatic = Tetris(width);
	gameDynamic = Tetris(width);

	pieceHeight = maxHeight;
	pieceId = "IJLOSTZ"[rand() % 7];
	piecePosition = width / 2 - 2;
	pieceHeight = maxHeight;
	pieceRotation = 0;
	score = 0;
}

//	Rotate table on Bebado mode
void Play::spinDisplay(const int x) {
	spin = spin + 3.0;
	if(spin > 360.0)
		spin = spin - 360.0;
	glutTimerFunc(100, spinDisplay, x);
	glutPostRedisplay();
}

//	Draw a square given coords and character
void Play::drawSquare(const GLint x, const GLint y, const char c) {
	if(c == ' ') {
		glColor3f(colors[color]["Text"][0], colors[color]["Text"][1], colors[color]["Text"][2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glColor3f(colors[color]["Piece"][0], colors[color]["Piece"][1], colors[color]["Piece"][2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glPushMatrix();
	if(option["BEBADO"])
		glRotatef(spin, 0.0, 0.0, 1.0);
	glTranslatef(-width * view_h / maxHeight +
	                 x * 2 * (GLfloat(view_h / maxHeight)),
	             -view_h + y * 2 * (GLfloat(view_h / maxHeight)), 0);
	glRectf(0, 0, 2 * view_h / maxHeight, 2 * view_h / maxHeight);
	glPopMatrix();
}

//	Draw current state gameStatic table
void Play::drawTable() {
	for(int i = 0; i < maxHeight; i++)
		for(int j = 0; j < width; j++)
			drawSquare(j, maxHeight - i - 1, gameDynamic.get(j, maxHeight - i - 1));
}

//	Render current game frame
void Play::renderGameFrame() {
	if(gameDynamic.getHeight() > maxHeight) {
		const string p = "PONTUACAO: " + to_string(score);
		drawText(make_pair(0, view_h * 0.1), make_pair(view_h * 0.0008, view_h * 0.0008), "VOCE PERDEU!");
		drawText(make_pair(0, -view_h * 0.1), make_pair(view_h * 0.0008, view_h * 0.0008), p);
		state = 3;
		return;
	}

	gameDynamic = gameStatic;

	if(lastKey == 'l') {
		Tetris jogoTeste = gameDynamic;
		if(jogoTeste.addPiece(piecePosition - 1, pieceHeight, pieceId, rotations[pieceRotation])) {
			piecePosition--;
		}
	} else if(lastKey == 'r') {
		Tetris jogoTeste = gameDynamic;
		if(jogoTeste.addPiece(piecePosition + 1, pieceHeight, pieceId, rotations[pieceRotation])) {
			piecePosition++;
		}
	} else if(lastKey == 's') {
		Tetris jogoTeste = gameDynamic;
		if(jogoTeste.addPiece(piecePosition, pieceHeight, pieceId, rotations[(pieceRotation + 1) % 4]))
			pieceRotation = (pieceRotation + 1) % 4;
	}

	if(gameDynamic.addPiece(piecePosition, pieceHeight - 1, pieceId, rotations[pieceRotation])) {
		pieceHeight--;
	} else {
		gameStatic.addPiece(piecePosition, pieceHeight, pieceId, rotations[pieceRotation]);
		gameDynamic = gameStatic;
		pieceId = "IJLOSTZ"[rand() % 7];
		piecePosition = width / 2 - 2;
		pieceHeight = maxHeight;
		pieceRotation = rand() % 4;
		score += gameDynamic.removeRows();
		height = gameDynamic.getHeight();
		gameStatic = gameDynamic;
	}
	drawTable();

	if(lastKey == 'a') {
		usleep(speed - speed * 0.8);
	} else {
		usleep(speed);
	}
	lastKey = ' ';
}

//	Set view variables to keep window ratio
void Play::setView(const GLfloat &view_w, const GLfloat &view_h) {
	Play::view_w = view_w;
	Play::view_h = view_h;
}

//	Draw text given text, scale and position
void Play::drawText(const pair<GLfloat, GLfloat>& pos, const pair<GLfloat, GLfloat>& scl, const string str) {
	const unsigned char* text = (unsigned char*)str.c_str();

	const GLfloat length = glutStrokeLength(GLUT_STROKE_MONO_ROMAN, text)*scl.first;
	const GLfloat height = glutStrokeHeight(GLUT_STROKE_MONO_ROMAN)*scl.second;

	glPushMatrix();
	glColor3f(colors[color]["Text"][0], colors[color]["Text"][1], colors[color]["Text"][2]);
	glLineWidth(2);
	glTranslatef(pos.first - length/2.0, pos.second - height/2.0, 0);
	glScalef(scl.first, scl.second, 1.0);
	glutStrokeString(GLUT_STROKE_MONO_ROMAN, text);
	glPopMatrix();
}