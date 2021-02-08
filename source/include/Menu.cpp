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
		{"NORMAL1", make_pair(-p1.first/2 - view_h*0.45, view_h*0.52)},
		{"RAPIDO", make_pair(-p1.first/2, view_h*0.52)},
		{"TURBO", make_pair(-1*(p1.first/2 - view_h*0.45), view_h*0.52)},
		{"20x10", make_pair(-p1.first/2 - view_h*0.45, view_h*0.22)},
		{"30x15", make_pair(-p1.first/2, view_h*0.22)},
		{"50x25", make_pair(-1*(p1.first/2 - view_h*0.45), view_h*0.22)},
		{"CORES1", make_pair(-p1.first/2 - view_h*0.45, -view_h*0.22-p1.second)},
		{"CORES2", make_pair(-p1.first/2, -view_h*0.22-p1.second)},
		{"CORES3", make_pair(-1*(p1.first/2 - view_h*0.45), -view_h*0.22-p1.second)},
		{"NORMAL2", make_pair(-p1.first/2 - view_h*0.25, -view_h*0.52-p1.second)},
		{"BEBADO", make_pair(-1*(p1.first/2 - view_h*0.25), -view_h*0.52-p1.second)},
		{"SAIR", make_pair(-p1.first/2, -view_h*0.8-p1.second)}
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
void Menu::drawText(const pair<GLfloat, GLfloat>& pos, const pair<GLfloat, GLfloat>& scl, const string str) {
	string out = str;
	if(out == "NORMAL1" || out == "NORMAL2")
		out = "NORMAL";
	const unsigned char* text = (unsigned char*)out.c_str();

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

//	Draw button given text and position
void Menu::drawButton(const pair<GLfloat, GLfloat> &pos, const string text) {
	glPushMatrix();
	glColor3f(colors[color]["BoxBack"][0], colors[color]["BoxBack"][1], colors[color]["BoxBack"][2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(5);
	glTranslatef(pos.first, pos.second, 0);
	glRecti(p0.first, p0.second, p1.first, p1.second);
	glPopMatrix();

	glPushMatrix();
	glColor3f(colors[color]["Box"][0], colors[color]["Box"][1], colors[color]["Box"][2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
		glPushMatrix();
		glColor3f(colors[color]["Text"][0], colors[color]["Text"][1], colors[color]["Text"][2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(5);
		glTranslatef(pos.first, pos.second, 0);
		glRecti(p0.first, p0.second, p1.first, p1.second);
		glPopMatrix();
	}

	drawText(make_pair(pos.first+p1.first/2.0, pos.second+p1.second/2.0), make_pair(sxmenu, symenu), text);
}

//	Render menu elements
void Menu::renderMenu() {
	//	Iniciar
	drawButton(boxPos[optNames[0]], optNames[0]);

	//	Velocidade
	drawText(
		make_pair(
			boxPos[optNames[0]].first + p1.first / 2,
			(boxPos[optNames[0]].second+p1.second + boxPos[optNames[2]].second)/2.0
		),
		make_pair(
			sxmenu,
			symenu
		),
		"VELOCIDADE"
	);
	drawButton(boxPos[optNames[1]], optNames[1]);
	drawButton(boxPos[optNames[2]], optNames[2]);
	drawButton(boxPos[optNames[3]], optNames[3]);

	//	Tamanho
	drawText(
		make_pair(
			boxPos[optNames[0]].first + p1.first / 2,
			(boxPos[optNames[2]].second+p1.second + boxPos[optNames[5]].second)/2.0
		),
		make_pair(
			sxmenu,
			symenu
		),
		"TAMANHO"
	);
	drawButton(boxPos[optNames[4]], optNames[4]);
	drawButton(boxPos[optNames[5]], optNames[5]);
	drawButton(boxPos[optNames[6]], optNames[6]);

	//	Cores
	drawText(
		make_pair(
			boxPos[optNames[0]].first + p1.first / 2,
			(boxPos[optNames[5]].second+p1.second + boxPos[optNames[8]].second)/2.0
		),
		make_pair(
			sxmenu,
			symenu
		),
		"CORES"
	);
	drawButton(boxPos[optNames[7]], optNames[7]);
	drawButton(boxPos[optNames[8]], optNames[8]);
	drawButton(boxPos[optNames[9]], optNames[9]);

	//	Modo
	drawText(
		make_pair(
			boxPos[optNames[0]].first + p1.first / 2,
			(boxPos[optNames[8]].second+p1.second + boxPos[optNames[10]].second)/2.0
		),
		make_pair(
			sxmenu,
			symenu
		),
		"MODO"
	);
	drawButton(boxPos[optNames[10]], optNames[10]);
	drawButton(boxPos[optNames[11]], optNames[11]);

	//	Sair
	drawButton(boxPos[optNames[12]], optNames[12]);
}