#include "Menu.h"

Menu::Menu(
		const unordered_map<string, unordered_map<string, vector<GLfloat>>> &colors,
		const string &cor, const unordered_map<string, bool> &option,
		const unordered_map<string, pair<int, bool>> &selecN,
		const GLfloat &view_w, const GLfloat &view_h) {
	this->colors = colors;
	this->cor = cor;
	this->option = option;
	this->selecN = selecN;
	this->view_w = view_w;
	this->view_h = view_h;
	this->sxmenu = view_h*0.0003;
	this->symenu = view_h*0.0004;
	this->p0 = make_pair(-view_h*0.1, -view_h*0.1);
	this->p1 = make_pair(view_h*0.3, view_h*0.03);
	this->boxPos = {
		{"INICIAR", make_pair(-(p0.first+p1.first)/2, view_h*0.8)},
		{"NORMAL1", make_pair(-(p0.first+p1.first)/2 - view_h*0.45, view_h*0.5)},
		{"RAPIDO", make_pair(-(p0.first+p1.first)/2, view_h*0.5)},
		{"TURBO", make_pair(-1*((p0.first+p1.first)/2 - view_h*0.45), view_h*0.5)},
		{"20x10", make_pair(-(p0.first+p1.first)/2 - view_h*0.45, view_h*0.2)},
		{"30x15", make_pair(-(p0.first+p1.first)/2, view_h*0.2)},
		{"50x25", make_pair(-1*((p0.first+p1.first)/2 - view_h*0.45), view_h*0.2)},
		{"Cores1", make_pair(-(p0.first+p1.first)/2 - view_h*0.45, -view_h*0.1)},
		{"Cores2", make_pair(-(p0.first+p1.first)/2, -view_h*0.1)},
		{"Cores3", make_pair(-1*((p0.first+p1.first)/2 - view_h*0.45), -view_h*0.1)},
		{"NORMAL2", make_pair(-(p0.first+p1.first)/2 - view_h*0.25, -view_h*0.4)},
		{"BEBADO", make_pair(-1*((p0.first+p1.first)/2 - view_h*0.25), -view_h*0.4)},
		{"SAIR", make_pair(-(p0.first+p1.first)/2, -view_h*0.7)}
	};
}

Menu::~Menu() {
	this->colors.clear();
	this->option.clear();
	this->selecN.clear();
}

Menu &Menu::operator=(const Menu *o) {
	this->colors = o->colors;
	this->p0 = o->p0;
	this->p1 = o->p1;
	this->cor = o->cor;
	this->option = o->option;
	this->selecN = o->selecN;
	this->view_w = o->view_w;
	this->view_h = o->view_h;
	this->boxPos = o->boxPos;
	this->sxmenu = o->sxmenu;
	this->symenu = o->symenu;

	return *this;
}

//	Define mouse pointer selection
string Menu::mousePointer(const GLint x, const GLint y) {
	for(auto key : optNames) {
		if(key == "TURBO" || key == "50x25" || key == "Cores3" ||
		   key == "BEBADO") {
			if(x >= p0.first + boxPos[key].first &&
			   x <= p1.first + boxPos[key].first &&
			   y >= p0.second + boxPos[key].second &&
			   y <= p1.second + boxPos[key].second)
				return key;
		} else if(x >= p0.first + boxPos[key].first &&
				  x <= p1.first + boxPos[key].first &&
				  y >= p0.second + boxPos[key].second &&
				  y <= p1.second + boxPos[key].second)
			return key;
	}
	return "";
}

//	Draw text given text, scale and position
void Menu::drawText(const GLint x, const GLint y, const GLfloat sx, const GLfloat sy, const string text) {
	glPointSize(1);
	glLineWidth(2);
	string out = text;
	if(out == "NORMAL1" || out == "NORMAL2")
		out = "NORMAL";
	glColor3f(colors[cor]["Text"][0], colors[cor]["Text"][1],
			  colors[cor]["Text"][2]);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(sx, sy, 1.0);
	for(int i = 0; i < out.length(); ++i) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, out[i]);
	}
	glPopMatrix();
}

//	Draw button given text and position
void Menu::drawButton(const pair<GLfloat, GLfloat> &pos, const string text) {
	glColor3f(colors[cor]["BoxBack"][0], colors[cor]["BoxBack"][1], colors[cor]["BoxBack"][2]);
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(5);
	glTranslatef(pos.first, pos.second, 0);
	glRecti(p0.first, p0.second, p1.first, p1.second);
	glPopMatrix();
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(colors[cor]["Box"][0], colors[cor]["Box"][1],
			  colors[cor]["Box"][2]);
	glPushMatrix();
	glTranslatef(pos.first, pos.second, 0);
	glRecti(p0.first, p0.second, p1.first, p1.second);
	glPopMatrix();
	if(option[text]) {
		glPushMatrix();
		glColor3f(colors[cor]["Background"][0], colors[cor]["Background"][1],
				  colors[cor]["Background"][2]);
		glTranslatef(pos.first, pos.second, 0);
		glRecti(p0.first, p0.second, p1.first, p1.second);
		glPopMatrix();
	}
	if(selecN[text].second) {
		glColor3f(colors[cor]["Text"][0], colors[cor]["Text"][1],
				  colors[cor]["Text"][2]);
		glPushMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(5);
		glTranslatef(pos.first, pos.second, 0);
		glRecti(p0.first, p0.second, p1.first, p1.second);
		glPopMatrix();
	}
	drawText(pos.first, pos.second - view_h * 0.05, sxmenu, symenu, text);
	glPopMatrix();
}

//	Render menu elements
void Menu::renderMenu() {
	//	Iniciar
	drawButton(boxPos[optNames[0]], optNames[0]);

	//	Velocidade
	drawText(-(p0.first + p1.first) / 2 - view_h * 0.05, view_h * 0.6, sxmenu, symenu, "VELOCIDADE");
	drawButton(boxPos[optNames[1]], optNames[1]);
	drawButton(boxPos[optNames[2]], optNames[2]);
	drawButton(boxPos[optNames[3]], optNames[3]);

	//	Tamanho
	drawText(-(p0.first + p1.first) / 2, view_h * 0.3, sxmenu, symenu, "TAMANHO");
	drawButton(boxPos[optNames[4]], optNames[4]);
	drawButton(boxPos[optNames[5]], optNames[5]);
	drawButton(boxPos[optNames[6]], optNames[6]);

	//	Cores
	drawText(-(p0.first + p1.first) / 2 + view_h * 0.02, view_h * 0.005, sxmenu, symenu, "CORES");
	drawButton(boxPos[optNames[7]], optNames[7]);
	drawButton(boxPos[optNames[8]], optNames[8]);
	drawButton(boxPos[optNames[9]], optNames[9]);

	//	Modo
	drawText(-(p0.first + p1.first) / 2 + view_h * 0.03, -view_h * 0.3, sxmenu, symenu, "MODO");
	drawButton(boxPos[optNames[10]], optNames[10]);
	drawButton(boxPos[optNames[11]], optNames[11]);

	//	Sair
	drawButton(boxPos[optNames[12]], optNames[12]);
}