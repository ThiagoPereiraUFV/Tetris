#include "Menu.h"

string Menu::color;
GLfloat Menu::view_w, Menu::view_h;
GLfloat Menu::sxmenu, Menu::symenu;
unordered_map<string, bool> Menu::option;
pair<GLfloat, GLfloat> Menu::p0, Menu::p1;
unordered_map<string, pair<int, bool>> Menu::selecN;
unordered_map<string, pair<GLfloat, GLfloat>> Menu::boxPos;
unordered_map<string, unordered_map<string, vector<GLfloat>>> Menu::colors;
vector<string> Menu::optNames{
	"INICIAR", "NORMAL1", "RAPIDO",
	"TURBO", "20x10", "30x15",
	"50x25", "CORES1", "CORES2",
	"CORES3", "NORMAL2", "BEBADO", "SAIR"
};

void Menu::setup(
		const unordered_map<string, unordered_map<string, vector<GLfloat>>> &colors,
		const string &color, const unordered_map<string, bool> &option,
		const unordered_map<string, pair<int, bool>> &selecN
	) {
	Menu::colors = colors;
	Menu::color = color;
	Menu::option = option;
	Menu::selecN = selecN;
}

//	Set view variables to keep window ratio
void Menu::setView(const GLfloat &view_w, const GLfloat &view_h) {
	Menu::view_w = view_w;
	Menu::view_h = view_h;
	sxmenu = view_h*0.0005;
	symenu = view_h*0.0006;
	p0 = make_pair(0, 0);
	p1 = make_pair(-view_h*0.4, -view_h*0.14);
	boxPos = {
		{"INICIAR", make_pair(-p1.first/2, view_h*0.8)},
		{"NORMAL1", make_pair(-p1.first/2 - view_h*0.45, view_h*0.5)},
		{"RAPIDO", make_pair(-p1.first/2, view_h*0.5)},
		{"TURBO", make_pair(-1*(p1.first/2 - view_h*0.45), view_h*0.5)},
		{"20x10", make_pair(-p1.first/2 - view_h*0.45, view_h*0.2)},
		{"30x15", make_pair(-p1.first/2, view_h*0.2)},
		{"50x25", make_pair(-1*(p1.first/2 - view_h*0.45), view_h*0.2)},
		{"CORES1", make_pair(-p1.first/2 - view_h*0.45, -view_h*0.1)},
		{"CORES2", make_pair(-p1.first/2, -view_h*0.1)},
		{"CORES3", make_pair(-1*(p1.first/2 - view_h*0.45), -view_h*0.1)},
		{"NORMAL2", make_pair(-p1.first/2 - view_h*0.25, -view_h*0.4)},
		{"BEBADO", make_pair(-1*(p1.first/2 - view_h*0.25), -view_h*0.4)},
		{"SAIR", make_pair(-p1.first/2, -view_h*0.7)}
	};
}

//	Define mouse pointer selection
string Menu::mousePointer(const GLint x, const GLint y) {
	for(auto key : optNames) {
		if(
			x <= p0.first + boxPos[key].first &&
			x >= p1.first + boxPos[key].first &&
			y <= p0.second + boxPos[key].second &&
			y >= p1.second + boxPos[key].second
		)
	return key;
	}
	return "";
}

//	Draw text given text, scale and position
void Menu::drawText(const GLfloat x, const GLfloat y, const GLfloat sx, const GLfloat sy, const string text) {
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

//	Draw button given text and position
void Menu::drawButton(const pair<GLfloat, GLfloat> &pos, const string text) {
	glColor3f(colors[color]["BoxBack"][0], colors[color]["BoxBack"][1], colors[color]["BoxBack"][2]);
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(5);
	glTranslatef(pos.first, pos.second, 0);
	glRecti(p0.first, p0.second, p1.first, p1.second);
	glPopMatrix();
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(colors[color]["Box"][0], colors[color]["Box"][1], colors[color]["Box"][2]);
	glPushMatrix();
	glTranslatef(pos.first, pos.second, 0);
	glRecti(p0.first, p0.second, p1.first, p1.second);
	glPopMatrix();
	if(option[text]) {
		glPushMatrix();
		glColor3f(colors[color]["Background"][0], colors[color]["Background"][1], colors[color]["Background"][2]);
		glTranslatef(pos.first, pos.second, 0);
		glRecti(p0.first, p0.second, p1.first, p1.second);
		glPopMatrix();
	}
	if(selecN[text].second) {
		glColor3f(colors[color]["Text"][0], colors[color]["Text"][1], colors[color]["Text"][2]);
		glPushMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(5);
		glTranslatef(pos.first, pos.second, 0);
		glRecti(p0.first, p0.second, p1.first, p1.second);
		glPopMatrix();
	}
	drawText(pos.first+p1.first/2.0, pos.second+p1.second/2.0, sxmenu, symenu, text);
	glPopMatrix();
}

//	Render menu elements
void Menu::renderMenu() {
	//	Iniciar
	drawButton(boxPos[optNames[0]], optNames[0]);

	//	Velocidade
	drawText(boxPos[optNames[0]].first + p1.first / 2, (boxPos[optNames[0]].second+p1.second + boxPos[optNames[2]].second)/2.0, sxmenu, symenu, "VELOCIDADE");
	drawButton(boxPos[optNames[1]], optNames[1]);
	drawButton(boxPos[optNames[2]], optNames[2]);
	drawButton(boxPos[optNames[3]], optNames[3]);

	//	Tamanho
	drawText(boxPos[optNames[0]].first + p1.first / 2, (boxPos[optNames[2]].second+p1.second + boxPos[optNames[5]].second)/2.0, sxmenu, symenu, "TAMANHO");
	drawButton(boxPos[optNames[4]], optNames[4]);
	drawButton(boxPos[optNames[5]], optNames[5]);
	drawButton(boxPos[optNames[6]], optNames[6]);

	//	Cores
	drawText(boxPos[optNames[0]].first + p1.first / 2, (boxPos[optNames[5]].second+p1.second + boxPos[optNames[8]].second)/2.0, sxmenu, symenu, "CORES");
	drawButton(boxPos[optNames[7]], optNames[7]);
	drawButton(boxPos[optNames[8]], optNames[8]);
	drawButton(boxPos[optNames[9]], optNames[9]);

	//	Modo
	drawText(boxPos[optNames[0]].first + p1.first / 2, (boxPos[optNames[8]].second+p1.second + boxPos[optNames[10]].second)/2.0, sxmenu, symenu, "MODO");
	drawButton(boxPos[optNames[10]], optNames[10]);
	drawButton(boxPos[optNames[11]], optNames[11]);

	//	Sair
	drawButton(boxPos[optNames[12]], optNames[12]);
}