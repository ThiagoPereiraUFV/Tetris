#include "Play.h"

int Play::state;
GLfloat Play::spin;
string Play::color;
pair<int, int> Play::tam;
GLfloat Play::view_w, Play::view_h;
char Play::idPecaAtual, Play::lastKey;
Tetris Play::jogo, Play::jogoComPecaCaindo;
int Play::posicaoPecaAtual, Play::rotacaoPecaAtual;
int Play::vel, Play::altura, Play::alturaOld, Play::pontos;
int Play::larguraJogo, Play::alturaMaximaJogo, Play::alturaPecaAtual;
unordered_map<string, bool> Play::option;
const vector<GLint> Play::possiveisRotacoes{0, 90, 180, 270};
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
void Play::exibeObjeto(const GLint x, const GLint y, const char c) {
	if(c == ' ') {
		glColor3f(1.0 - colors[color]["Piece"][0], 1.0 - colors[color]["Piece"][1],
		          1.0 - colors[color]["Piece"][2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glColor3f(colors[color]["Piece"][0], colors[color]["Piece"][1],
		          colors[color]["Piece"][2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glPushMatrix();
	if(option["BEBADO"])
		glRotatef(spin, 0.0, 0.0, 1.0);
	glTranslatef(-larguraJogo * view_h / alturaMaximaJogo +
	                 x * 2 * (GLfloat(view_h / alturaMaximaJogo)),
	             -view_h + y * 2 * (GLfloat(view_h / alturaMaximaJogo)), 0);
	glRectf(0, 0, 2 * view_h / alturaMaximaJogo, 2 * view_h / alturaMaximaJogo);
	glPopMatrix();
}

//	Funcao utilizada para desenhar o estado atual do tabuleiro do jogo
void Play::exibeJogo() {
	for(int i = 0; i < alturaMaximaJogo; i++)
		for(int j = 0; j < larguraJogo; j++)
			exibeObjeto(j, alturaMaximaJogo - i - 1, jogoComPecaCaindo.get(j, alturaMaximaJogo - i - 1));
}

//	Funcao utilizada para renderizar o frame atual do jogo e posicionar uma peca
void Play::renderGameFrame() {
	glClear(GL_COLOR_BUFFER_BIT);
	if(jogoComPecaCaindo.getAltura() > alturaMaximaJogo) {
		const string p = "PONTUACAO: " + to_string(pontos);
		drawText(-view_h * 0.35, view_h * 0.3, view_h * 0.0008, view_h * 0.0008, "VOCE PERDEU!");
		drawText(-view_h * 0.35, view_h * 0.1, view_h * 0.0008, view_h * 0.0008, p);
		state = 3;
		return;
	}
	jogoComPecaCaindo = jogo;

	if(lastKey == 'l') {
		Tetris jogoTeste = jogoComPecaCaindo;
		if(jogoTeste.adicionaForma(posicaoPecaAtual - 1, alturaPecaAtual,
		                           idPecaAtual,
		                           possiveisRotacoes[rotacaoPecaAtual]))
			posicaoPecaAtual--;
	} else if(lastKey == 'r') {
		Tetris jogoTeste = jogoComPecaCaindo;
		if(jogoTeste.adicionaForma(posicaoPecaAtual + 1, alturaPecaAtual,
		                           idPecaAtual,
		                           possiveisRotacoes[rotacaoPecaAtual]))
			posicaoPecaAtual++;
	} else if(lastKey == 's') {
		Tetris jogoTeste = jogoComPecaCaindo;
		if(jogoTeste.adicionaForma(
		       posicaoPecaAtual, alturaPecaAtual, idPecaAtual,
		       possiveisRotacoes[(rotacaoPecaAtual + 1) % 4]))
			rotacaoPecaAtual = (rotacaoPecaAtual + 1) % 4;
	}

	if(jogoComPecaCaindo.adicionaForma(posicaoPecaAtual, alturaPecaAtual - 1, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual])) {
		alturaPecaAtual--;
	} else {
		jogo.adicionaForma(posicaoPecaAtual, alturaPecaAtual, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]);
		jogoComPecaCaindo = jogo;
		idPecaAtual = "IJLOSTZ"[rand() % 7];
		posicaoPecaAtual = larguraJogo / 2 - 2;
		alturaPecaAtual = alturaMaximaJogo;
		rotacaoPecaAtual = rand() % 4;
		alturaOld = jogoComPecaCaindo.getAltura();
		jogoComPecaCaindo.removeLinhasCompletas();
		altura = jogoComPecaCaindo.getAltura();
		if(altura != alturaOld)
			pontos++;
		jogo = jogoComPecaCaindo;
	}
	exibeJogo();
	if(lastKey == 'a')
		usleep(vel - vel * 0.8);
	else
		usleep(vel);
	lastKey = ' ';
}

//	Funcao utilizada para configurar inicializar o tamanho do tabuleiro
void Play::configGame() {
	alturaMaximaJogo = tam.first;
	larguraJogo = tam.second;
	jogo = Tetris(larguraJogo);
	jogoComPecaCaindo = Tetris(larguraJogo);

	alturaPecaAtual = alturaMaximaJogo;
	idPecaAtual = "IJLOSTZ"[rand() % 7];
	posicaoPecaAtual = larguraJogo / 2 - 2;
	alturaPecaAtual = alturaMaximaJogo;
	rotacaoPecaAtual = 0;
	pontos = 0;
}

//	Funcao utilizada para determinar o tamanho desejado do tabuleiro, alem da velocidade e o modo bebado
void Play::configVars() {
	if(option["20x10"]) {
		tam = make_pair(20, 10);
		if(option["NORMAL1"])
			vel = 200000;
		else if(option["RAPIDO"])
			vel = 80000;
		else
			vel = 70000;
	} else if(option["30x15"]) {
		tam = make_pair(30, 15);
		if(option["NORMAL1"])
			vel = 80000;
		else if(option["RAPIDO"])
			vel = 60000;
		else
			vel = 40000;
	} else {
		tam = make_pair(50, 25);
		if(option["NORMAL1"])
			vel = 50000;
		else if(option["RAPIDO"])
			vel = 40000;
		else
			vel = 30000;
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

//	Funcao utilizada para desenhar um texto dada uma posicao e uma escala
void Play::drawText(const GLint x, const GLint y, const GLfloat sx, const GLfloat sy, const string text) {
	glPointSize(1);
	glLineWidth(2);
	string out = text;
	if(out == "NORMAL1" || out == "NORMAL2")
		out = "NORMAL";
	glColor3f(colors[color]["Text"][0], colors[color]["Text"][1],
			  colors[color]["Text"][2]);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(sx, sy, 1.0);
	for(int i = 0; i < out.length(); ++i) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, out[i]);
	}
	glPopMatrix();
}