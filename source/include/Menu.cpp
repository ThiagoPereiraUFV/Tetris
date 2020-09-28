#include "Menu.h"
using namespace std;

//	Funcao utilizada para definir sobre qual botao o ponteiro do mouse se encontra
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

//	Funcao utilizada para desenhar um texto dada uma posicao e uma escala
void Menu::drawText(const GLint x, const GLint y, const GLfloat sx, const GLfloat sy,
			  const string text) {
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

//	Funcao utilizada para desenhar um botao dada uma posicao e um texto
void Menu::drawButton(const pair<GLfloat, GLfloat> &pos, const string text) {
	glColor3f(colors[cor]["BoxBack"][0], colors[cor]["BoxBack"][1],
			  colors[cor]["BoxBack"][2]);
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

//	Funcao utilizada para renderizar todos o menu
void Menu::renderMenu() {
	//	Iniciar
	drawButton(boxPos[optNames[0]], optNames[0]);

	//	Velocidade
	drawText(-(p0.first + p1.first) / 2 - view_h * 0.05, view_h * 0.6, sxmenu,
			 symenu, "VELOCIDADE");
	drawButton(boxPos[optNames[1]], optNames[1]);
	drawButton(boxPos[optNames[2]], optNames[2]);
	drawButton(boxPos[optNames[3]], optNames[3]);

	//	Tamanho
	drawText(-(p0.first + p1.first) / 2, view_h * 0.3, sxmenu, symenu,
			 "TAMANHO");
	drawButton(boxPos[optNames[4]], optNames[4]);
	drawButton(boxPos[optNames[5]], optNames[5]);
	drawButton(boxPos[optNames[6]], optNames[6]);

	//	Cores
	drawText(-(p0.first + p1.first) / 2 + view_h * 0.02, view_h * 0.005, sxmenu,
			 symenu, "CORES");
	drawButton(boxPos[optNames[7]], optNames[7]);
	drawButton(boxPos[optNames[8]], optNames[8]);
	drawButton(boxPos[optNames[9]], optNames[9]);

	//	Modo
	drawText(-(p0.first + p1.first) / 2 + view_h * 0.03, -view_h * 0.3, sxmenu,
			 symenu, "MODO");
	drawButton(boxPos[optNames[10]], optNames[10]);
	drawButton(boxPos[optNames[11]], optNames[11]);

	//	Sair
	drawButton(boxPos[optNames[12]], optNames[12]);
}