#include "Game.h"

using namespace std;

char Game::ultimaTecla = ' ';
int Game::state = 0, Game::selec = 0;
bool Game::gameRunning = false;
GLfloat Game::view_w = WINDOW_WIDTH/2;
GLfloat Game::view_h = WINDOW_HEIGHT/2;
unordered_map<string, bool> Game::option = {
	{"NORMAL1", 1}, {"RAPIDO", 0},
	{"TURBO", 0}, {"20x10", 1},
	{"30x15", 0}, {"50x25", 0},
	{"Cores1", 1}, {"Cores2", 0},
	{"Cores3", 0}, {"NORMAL2", 1}, {"BEBADO", 0}
};
unordered_map<string, pair<int, bool>> Game::selecN = {
	{"INICIAR", make_pair(0, 1)}, {"NORMAL1", make_pair(1, 0)},
	{"RAPIDO", make_pair(2, 0)}, {"TURBO", make_pair(3, 0)},
	{"20x10", make_pair(4, 0)}, {"30x15", make_pair(5, 0)},
	{"50x25", make_pair(6, 0)}, {"Cores1", make_pair(7, 0)},
	{"Cores2", make_pair(8, 0)}, {"Cores3", make_pair(9, 0)},
	{"NORMAL2", make_pair(10, 0)}, {"BEBADO", make_pair(11, 0)}, {"SAIR", make_pair(12, 0)}
};
unordered_map<int, string> Game::selecI = {
	{0, "INICIAR"}, {1, "NORMAL1"},
	{2, "RAPIDO"}, {3, "TURBO"},
	{4, "20x10"}, {5, "30x15"},
	{6, "50x25"}, {7, "Cores1"},
	{8, "Cores2"}, {9, "Cores3"},
	{10, "NORMAL2"}, {11, "BEBADO"}, {12, "SAIR"}
};
unordered_map<string, unordered_map<string, vector<GLfloat>>> Game::colors = {
	{"Cores1", {
		{"Box", {0.0, 0.0, 0.0}},
		{"BoxBack", {0.0, 0.0, 0.0}},
		{"Text", {1.0, 0.0, 0.0}},
		{"Background", {1.0, 1.0, 0.0}},
		{"Piece", {0.0, 0.0, 0.0}}}
	},
	{"Cores2", {
		{"Box", {0.015, 0.34, 0.87}},
		{"BoxBack", {0.0, 0.0, 0.0}},
		{"Text", {0.0, 1.0, 0.0}},
		{"Background", {1.0, 1.0, 1.0}},
		{"Piece", {0.015, 0.34, 0.87}}}
	},
	{"Cores3", {
		{"Box", {0.0, 0.0, 0.0}},
		{"BoxBack", {0.0, 0.0, 0.0}},
		{"Text", {1.0, 1.0, 0.0}},
		{"Background", {1.0, 0.0, 0.0}},
		{"Piece", {0.0, 0.0, 0.0}}}
	}
};
string Game::cor = (option["Cores1"]) ? "Cores1" : (option["Cores2"]) ? "Cores2" : "Cores3";
Menu Game::menu = *(new Menu(colors, cor, option, selecN, view_w, view_h));
Play Game::play = *(new Play(colors, cor, option, view_w, view_h, state, gameRunning));

void Game::game(int argc, char** argv) {
	glutInit(&argc, argv);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(HandleKeyboard);
	glutMouseFunc(HandleMouse);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutMainLoop();
}

//	Funcao utilizada para atualizar variaveis importantes que dependem do tamanho atual da janela por exemplo
void Game::updateVariables() {
	cor = (option["Cores1"]) ? "Cores1" : (option["Cores2"]) ? "Cores2" : "Cores3";
	glClearColor(
		colors[cor]["Background"][0],
		colors[cor]["Background"][1],
		colors[cor]["Background"][2], 1.0
	);

	menu = new Menu(colors, cor, option, selecN, view_w, view_h);
	play = new Play(colors, cor, option, view_w, view_h, state, gameRunning);
}

//	Funcao principal para renderizar os graficos do jogo
void Game::display() {
	glClear(GL_COLOR_BUFFER_BIT);
	updateVariables();
	if(state == 0) {
		menu.renderMenu();
	} else if(state == 1) {
		if(!gameRunning) {
			srand(time(NULL));
			play.configVars();
			play.configGame();
			gameRunning = 1;
		}
		play.renderGameFrame();
	} else if(state == 2) {
		usleep(3000000);
		state = 0;
	} else {
		exit(0);
	}
	/*
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f(0, view_h);
		glVertex2f(0, -view_h);
		glVertex2f(view_w, 0);
		glVertex2f(-view_w, 0);
	glEnd();
	*/
	glutSwapBuffers();
	glutPostRedisplay();
}

//	Redimensiona os objetos desenhados na tela e mantelos na mesma proporcao da janela
void Game::reshape(const GLsizei w, const GLsizei h) {
	view_w = w / 2;
	view_h = h / 2;
	updateVariables();
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
	glutPostRedisplay();
}

//	Funcao utilizada para tratar o uso das setas direcionais no menu ou durante
// o jogo
void Game::SpecialKeys(const int key, const int x, const int y) {
	if(state == 0) {
		switch(key) {
			case GLUT_KEY_UP:
				if(selecN["INICIAR"].second) {
					selec = selecN["SAIR"].first;
					selecN["SAIR"].second = 1;
					selecN["INICIAR"].second = 0;
				} else if(selecN["SAIR"].second) {
					selec = selecN["NORMAL2"].first;
					selecN["NORMAL2"].second = 1;
					selecN["SAIR"].second = 0;
				} else if(selecN["NORMAL2"].second || selecN["BEBADO"].second) {
					selec = selecN["Cores1"].first;
					selecN["Cores1"].second = 1;
					selecN["NORMAL2"].second = selecN["BEBADO"].second = 0;
				} else if(selecN["Cores1"].second || selecN["Cores2"].second ||
						  selecN["Cores3"].second) {
					selec = selecN["20x10"].first;
					selecN["20x10"].second = 1;
					selecN["Cores1"].second = selecN["Cores2"].second =
						selecN["Cores3"].second = 0;
				} else if(selecN["20x10"].second || selecN["30x15"].second ||
						  selecN["50x25"].second) {
					selec = selecN["NORMAL1"].first;
					selecN["NORMAL1"].second = 1;
					selecN["20x10"].second = selecN["30x15"].second =
						selecN["50x25"].second = 0;
				} else if(selecN["NORMAL1"].second || selecN["RAPIDO"].second ||
						  selecN["TURBO"].second) {
					selec = selecN["INICIAR"].first;
					selecN["INICIAR"].second = 1;
					selecN["NORMAL1"].second = selecN["RAPIDO"].second =
						selecN["TURBO"].second = 0;
				}
				break;
			case GLUT_KEY_DOWN:
				if(selecN["INICIAR"].second) {
					selec = selecN["NORMAL1"].first;
					selecN["NORMAL1"].second = 1;
					selecN["INICIAR"].second = 0;
				} else if(selecN["NORMAL1"].second || selecN["RAPIDO"].second ||
						  selecN["TURBO"].second) {
					selec = selecN["20x10"].first;
					selecN["20x10"].second = 1;
					selecN["NORMAL1"].second = selecN["RAPIDO"].second =
						selecN["TURBO"].second = 0;
				} else if(selecN["20x10"].second || selecN["30x15"].second ||
						  selecN["50x25"].second) {
					selec = selecN["Cores1"].first;
					selecN["Cores1"].second = 1;
					selecN["20x10"].second = selecN["30x15"].second =
						selecN["50x25"].second = 0;
				} else if(selecN["Cores1"].second || selecN["Cores2"].second ||
						  selecN["Cores3"].second) {
					selec = selecN["NORMAL2"].first;
					selecN["NORMAL2"].second = 1;
					selecN["Cores1"].second = selecN["Cores2"].second =
						selecN["Cores3"].second = 0;
				} else if(selecN["NORMAL2"].second || selecN["BEBADO"].second) {
					selec = selecN["SAIR"].first;
					selecN["SAIR"].second = 1;
					selecN["NORMAL2"].second = selecN["BEBADO"].second = 0;
				} else if(selecN["SAIR"].second) {
					selec = selecN["INICIAR"].first;
					selecN["INICIAR"].second = 1;
					selecN["SAIR"].second = 0;
				}
				break;
			case GLUT_KEY_RIGHT:
				if(selecN["NORMAL1"].second) {
					selec = selecN["RAPIDO"].first;
					selecN["RAPIDO"].second = 1;
					selecN["NORMAL1"].second = 0;
				} else if(selecN["RAPIDO"].second) {
					selec = selecN["TURBO"].first;
					selecN["TURBO"].second = 1;
					selecN["RAPIDO"].second = 0;
				} else if(selecN["TURBO"].second) {
					selec = selecN["NORMAL1"].first;
					selecN["NORMAL1"].second = 1;
					selecN["TURBO"].second = 0;
				}
				if(selecN["20x10"].second) {
					selec = selecN["30x15"].first;
					selecN["30x15"].second = 1;
					selecN["20x10"].second = 0;
				} else if(selecN["30x15"].second) {
					selec = selecN["50x25"].first;
					selecN["50x25"].second = 1;
					selecN["30x15"].second = 0;
				} else if(selecN["50x25"].second) {
					selec = selecN["20x10"].first;
					selecN["20x10"].second = 1;
					selecN["50x25"].second = 0;
				}
				if(selecN["Cores1"].second) {
					selec = selecN["Cores2"].first;
					selecN["Cores2"].second = 1;
					selecN["Cores1"].second = 0;
				} else if(selecN["Cores2"].second) {
					selec = selecN["Cores3"].first;
					selecN["Cores3"].second = 1;
					selecN["Cores2"].second = 0;
				} else if(selecN["Cores3"].second) {
					selec = selecN["Cores1"].first;
					selecN["Cores1"].second = 1;
					selecN["Cores3"].second = 0;
				}
				if(selecN["NORMAL2"].second) {
					selec = selecN["BEBADO"].first;
					selecN["BEBADO"].second = 1;
					selecN["NORMAL2"].second = 0;
				} else if(selecN["BEBADO"].second) {
					selec = selecN["NORMAL2"].first;
					selecN["NORMAL2"].second = 1;
					selecN["BEBADO"].second = 0;
				}
				break;
			case GLUT_KEY_LEFT:
				if(selecN["NORMAL1"].second) {
					selec = selecN["TURBO"].first;
					selecN["TURBO"].second = 1;
					selecN["NORMAL1"].second = 0;
				} else if(selecN["TURBO"].second) {
					selec = selecN["RAPIDO"].first;
					selecN["RAPIDO"].second = 1;
					selecN["TURBO"].second = 0;
				} else if(selecN["RAPIDO"].second) {
					selec = selecN["NORMAL1"].first;
					selecN["NORMAL1"].second = 1;
					selecN["RAPIDO"].second = 0;
				}
				if(selecN["20x10"].second) {
					selec = selecN["50x25"].first;
					selecN["50x25"].second = 1;
					selecN["20x10"].second = 0;
				} else if(selecN["50x25"].second) {
					selec = selecN["30x15"].first;
					selecN["30x15"].second = 1;
					selecN["50x25"].second = 0;
				} else if(selecN["30x15"].second) {
					selec = selecN["20x10"].first;
					selecN["20x10"].second = 1;
					selecN["30x15"].second = 0;
				}
				if(selecN["Cores1"].second) {
					selec = selecN["Cores3"].first;
					selecN["Cores3"].second = 1;
					selecN["Cores1"].second = 0;
				} else if(selecN["Cores3"].second) {
					selec = selecN["Cores2"].first;
					selecN["Cores2"].second = 1;
					selecN["Cores3"].second = 0;
				} else if(selecN["Cores2"].second) {
					selec = selecN["Cores1"].first;
					selecN["Cores1"].second = 1;
					selecN["Cores2"].second = 0;
				}
				if(selecN["NORMAL2"].second) {
					selec = selecN["BEBADO"].first;
					selecN["BEBADO"].second = 1;
					selecN["NORMAL2"].second = 0;
				} else if(selecN["BEBADO"].second) {
					selec = selecN["NORMAL2"].first;
					selecN["NORMAL2"].second = 1;
					selecN["BEBADO"].second = 0;
				}
				break;
		}
		updateVariables();
	} else if(state == 1) {
		switch(key) {
			case GLUT_KEY_LEFT:
				ultimaTecla = 'l';
				break;
			case GLUT_KEY_RIGHT:
				ultimaTecla = 'r';
				break;
			case GLUT_KEY_DOWN:
				ultimaTecla = 'a';
				break;
		}
	}
	glutPostRedisplay();
}

//	Trata o uso das teclas enter, esc e spacebar no menu ou durante o jogos
void Game::HandleKeyboard(const unsigned char key, const int x, const int y) {
	if(state == 0) {
		switch(key) {
			case 13:
				if(selecI[selec] == "NORMAL1" || selecI[selec] == "RAPIDO" ||
				   selecI[selec] == "TURBO") {
					option["NORMAL1"] = option["RAPIDO"] = option["TURBO"] = 0;
					option[selecI[selec]] = 1;
				} else if(selecI[selec] == "20x10" ||
						  selecI[selec] == "30x15" ||
						  selecI[selec] == "50x25") {
					option["20x10"] = option["30x15"] = option["50x25"] = 0;
					option[selecI[selec]] = 1;
				} else if(selecI[selec] == "Cores1" ||
						  selecI[selec] == "Cores2" ||
						  selecI[selec] == "Cores3") {
					option["Cores1"] = option["Cores2"] = option["Cores3"] = 0;
					option[selecI[selec]] = 1;
				} else if(selecI[selec] == "NORMAL2" ||
						  selecI[selec] == "BEBADO") {
					option["NORMAL2"] = option["BEBADO"] = 0;
					option[selecI[selec]] = 1;
				}
				if(selecI[selec] == "INICIAR")
					state = 1;
				if(selecI[selec] == "SAIR")
					state = 3;
				break;
			case 27:
				selecN[selecI[selec]].second = 0;
				selecN["SAIR"].second = 1;
				selec = selecN["SAIR"].first;
				break;
		}
		updateVariables();
	} else if(state == 1) {
		switch(key) {
			case 27:
				state = 0;
				gameRunning = 0;
			case 32:
				ultimaTecla = 's';
				break;
		}
	}
	glutPostRedisplay();
}

//	Funcao utilizada para tratar o uso do mouse ao selecionar as opcoes do menu
void Game::HandleMouse(const int button, const int btnState, const int x, const int y) {
	if(state == 0) {
		switch(button) {
			case GLUT_LEFT_BUTTON:
				if(btnState == GLUT_DOWN) {
					// cout << "n(" << x - view_w << ", " <<  view_h - y <<
					// ")\n";
					const string cursorSelec = menu.mousePointer(x - view_w, view_h - y);
					if(cursorSelec.length()) {
						if(cursorSelec == "INICIAR")
							state = 1;
						else if(cursorSelec == "NORMAL1" ||
								cursorSelec == "RAPIDO" ||
								cursorSelec == "TURBO") {
							option["NORMAL1"] = 0;
							option["RAPIDO"] = 0;
							option["TURBO"] = 0;
							option[cursorSelec] = 1;
						} else if(cursorSelec == "20x10" ||
								  cursorSelec == "30x15" ||
								  cursorSelec == "50x25") {
							option["20x10"] = 0;
							option["30x15"] = 0;
							option["50x25"] = 0;
							option[cursorSelec] = 1;
						} else if(cursorSelec == "Cores1" ||
								  cursorSelec == "Cores2" ||
								  cursorSelec == "Cores3") {
							option["Cores1"] = 0;
							option["Cores2"] = 0;
							option["Cores3"] = 0;
							option[cursorSelec] = 1;
						} else if(cursorSelec == "NORMAL2" ||
								  cursorSelec == "BEBADO") {
							option["NORMAL2"] = 0;
							option["BEBADO"] = 0;
							option[cursorSelec] = 1;
						} else {
							state = 3;
						}
					}
				}
		}
		updateVariables();
	}
	glutPostRedisplay();
}

//	Trata do posicionamento do retangulo de selecao durante o uso do mouse no menu
void Game::MousePassiveMotion(const int x, const int y) {
	if(state == 0) {
		const string cursorSelec = menu.mousePointer(x - view_w, view_h - y);
		if(cursorSelec.length()) {
			selecN[selecI[selec]].second = 0;
			selecN[cursorSelec].second = 1;
			selec = selecN[cursorSelec].first;
		}
	}
	glutPostRedisplay();
}

//	Inicializar funcoes do openGl e ajustar posicao, largura e altura da janela
void Game::init() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2
	);
	glutCreateWindow("Tetris v1.0 by Thiago Pereira");
}