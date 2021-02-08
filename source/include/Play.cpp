#include "Play.h"

int Play::state;
GLfloat Play::spin;
string Play::color;
pair<int, int> Play::tableSize;
GLfloat Play::view_w, Play::view_h;
char Play::idPecaAtual, Play::lastKey;
Tetris Play::gameStatic, Play::gameDynamic;
int Play::piecePosition, Play::pieceRotation;
int Play::speed, Play::height, Play::lastHeight, Play::score;
int Play::width, Play::maxHeight, Play::pieceHeight;
unordered_map<string, bool> Play::option;
const vector<GLint> Play::rotations{0, 90, 180, 270};
unordered_map<string, unordered_map<string, vector<GLfloat>>> Play::colors;

void Play::setup(
		const unordered_map<string, unordered_map<string, vector<GLfloat>>> &colors,
		const string &color, const unordered_map<string, bool> &option
	) {
	spin = 0;
	Play::colors = colors;
	Play::color = color;
	Play::option = option;
}

//	Funcao utilizada para rotacionar o tabuleiro no modo bebado
void Play::spinDisplay(const int x) {
	spin = spin + 3.0;
	if(spin > 360.0)
		spin = spin - 360.0;
	glutTimerFunc(100, spinDisplay, x);
	glutPostRedisplay();
}

//	Funcao utilizada para desenhar um quadrado dada uma posicao e um caractere
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

//	Funcao utilizada para desenhar o estado atual do tabuleiro do gameStatic
void Play::drawTable() {
	for(int i = 0; i < maxHeight; i++)
		for(int j = 0; j < width; j++)
			drawSquare(j, maxHeight - i - 1, gameDynamic.get(j, maxHeight - i - 1));
}

//	Funcao utilizada para renderizar o frame atual do gameStatic e posicionar uma peca
void Play::renderGameFrame() {
	glClear(GL_COLOR_BUFFER_BIT);
	if(gameDynamic.getAltura() > maxHeight) {
		const string p = "PONTUACAO: " + to_string(score);
		drawText(0, view_h * 0.1, view_h * 0.0008, view_h * 0.0008, "VOCE PERDEU!");
		drawText(0, -view_h * 0.1, view_h * 0.0008, view_h * 0.0008, p);
		state = 3;
		return;
	}
	gameDynamic = gameStatic;

	if(lastKey == 'l') {
		Tetris jogoTeste = gameDynamic;
		if(jogoTeste.adicionaForma(piecePosition - 1, pieceHeight,
		                           idPecaAtual,
		                           rotations[pieceRotation]))
			piecePosition--;
	} else if(lastKey == 'r') {
		Tetris jogoTeste = gameDynamic;
		if(jogoTeste.adicionaForma(piecePosition + 1, pieceHeight,
		                           idPecaAtual,
		                           rotations[pieceRotation]))
			piecePosition++;
	} else if(lastKey == 's') {
		Tetris jogoTeste = gameDynamic;
		if(jogoTeste.adicionaForma(
		       piecePosition, pieceHeight, idPecaAtual,
		       rotations[(pieceRotation + 1) % 4]))
			pieceRotation = (pieceRotation + 1) % 4;
	}

	if(gameDynamic.adicionaForma(piecePosition, pieceHeight - 1, idPecaAtual, rotations[pieceRotation])) {
		pieceHeight--;
	} else {
		gameStatic.adicionaForma(piecePosition, pieceHeight, idPecaAtual, rotations[pieceRotation]);
		gameDynamic = gameStatic;
		idPecaAtual = "IJLOSTZ"[rand() % 7];
		piecePosition = width / 2 - 2;
		pieceHeight = maxHeight;
		pieceRotation = rand() % 4;
		lastHeight = gameDynamic.getAltura();
		gameDynamic.removeLinhasCompletas();
		height = gameDynamic.getAltura();
		if(height != lastHeight)
			score++;
		gameStatic = gameDynamic;
	}
	drawTable();
	if(lastKey == 'a')
		usleep(speed - speed * 0.8);
	else
		usleep(speed);
	lastKey = ' ';
}

//	Funcao utilizada para configurar inicializar o tamanho do tabuleiro
void Play::setUpGame() {
	maxHeight = tableSize.first;
	width = tableSize.second;
	gameStatic = Tetris(width);
	gameDynamic = Tetris(width);

	pieceHeight = maxHeight;
	idPecaAtual = "IJLOSTZ"[rand() % 7];
	piecePosition = width / 2 - 2;
	pieceHeight = maxHeight;
	pieceRotation = 0;
	score = 0;
}

//	Funcao utilizada para determinar o tamanho desejado do tabuleiro, alem da velocidade e o modo bebado
void Play::setUpVars() {
	if(option["20x10"]) {
		tableSize = make_pair(20, 10);
		if(option["NORMAL1"])
			speed = 200000;
		else if(option["RAPIDO"])
			speed = 80000;
		else
			speed = 70000;
	} else if(option["30x15"]) {
		tableSize = make_pair(30, 15);
		if(option["NORMAL1"])
			speed = 80000;
		else if(option["RAPIDO"])
			speed = 60000;
		else
			speed = 40000;
	} else {
		tableSize = make_pair(50, 25);
		if(option["NORMAL1"])
			speed = 50000;
		else if(option["RAPIDO"])
			speed = 40000;
		else
			speed = 30000;
	}
	if(option["BEBADO"]) {
		spin = 0.0;
		glutTimerFunc(100, spinDisplay, 0);
	}
}

//	Set view variables to keep window ratio
void Play::setView(const GLfloat &view_w, const GLfloat &view_h) {
	Play::view_w = view_w;
	Play::view_h = view_h;
}

//	Draw text given text, scale and position
void Play::drawText(const GLfloat x, const GLfloat y, const GLfloat sx, const GLfloat sy, const string text) {
	glPointSize(1);
	glLineWidth(2);
	string out = text;
	if(out == "NORMAL1" || out == "NORMAL2")
		out = "NORMAL";
	const unsigned char* str = (unsigned char*)out.c_str();
	const GLfloat length = glutStrokeLength(GLUT_STROKE_MONO_ROMAN, str)*sx;
	const GLfloat height = glutStrokeHeight(GLUT_STROKE_MONO_ROMAN)*sy;
	glColor3f(colors[color]["Text"][0], colors[color]["Text"][1], colors[color]["Text"][2]);
	glPushMatrix();
	glTranslatef(x - length/2.0, y - height/2.0, 0);
	glScalef(sx, sy, 1.0);
	glutStrokeString(GLUT_STROKE_MONO_ROMAN, str);
	glPopMatrix();
}