#include "Tetris.h"
#include <iostream>

Tetris::Tetris(const int width) {
	build(width);
}

void Tetris::build(const int width) {
	game = new char*[width];
	heights.resize(width);
	for(int i = 0; i < width; i++) {
		game[i] = NULL;
		heights[i] = 0;
	}
	this->width = width;
}

int Tetris::getHeight() const {
	int mx = 0;
	for(int i = 0; i < width; i++) mx = std::max(mx, heights[i]);
	return mx;
}

void Tetris::removeColumns(const int col) {
	delete []game[col];
	char **novoJogo = new char*[width-1];
	vector<int> novaAlturas(width-1);
	for(int i = 0; i < col; i++) {
		novoJogo[i] = game[i];
		novaAlturas[i] = heights[i];
	}
	for(int i = col+1; i < width; i++) {
		novoJogo[i-1] = game[i];
		novaAlturas[i-1] =heights[i];
	}
	delete []game;
	game = novoJogo;
	heights = novaAlturas;
	width--;

}


bool Tetris::isRowComplete(const int r) const {
	for(int i = 0; i < width; i++) {
		if(r >= heights[i] || game[i][r] == ' ') return false;
	}
	return true;
}

#include <cassert>
void Tetris::removeRow(const int r) {
	for(int i = 0; i < width; i++) {
		assert(r < heights[i]);
		char *newColumn;
		if(heights[i] == 1) {
			newColumn = NULL;
		} else newColumn = new char[heights[i]-1];

		for(int j = 0; j < r; j++) newColumn[j] = game[i][j];
		for(int j = r+1; j < heights[i]; j++) newColumn[j-1] = game[i][j];

		delete []game[i];
		game[i] = newColumn;
		heights[i]--;

		int maxHeightNewColumn = 0;
		for(int j = 0; j < heights[i]; j++) {
			if(newColumn[j] != ' ') maxHeightNewColumn = j+1;
		}
		if(maxHeightNewColumn != heights[i]) {
			//devido a uma remocao precisamos deixar essa col mais justa!
			char *newNewColumn = new char[maxHeightNewColumn];
			heights[i] = maxHeightNewColumn;
			for(int j = 0; j < maxHeightNewColumn; j++) newNewColumn[j] = newColumn[j];
			delete []game[i];
			game[i] = newNewColumn;
		}
	}
}

void Tetris::removeRows() {
	int maxHeight = getHeight();
	for(int i = 0; i < maxHeight; i++) {
		if(isRowComplete(i)) {
			removeRow(i);
			maxHeight--; //uma row foi removida!
			i--; //para testar a mesma row denovo (ja que tabuleiro foi deslocado para baixo...)
		}
	}
}

int Tetris::getColumnsNum() const {
	return width;
}

Tetris::~Tetris() {
	for(int i = 0; i < width; i++) delete []game[i];
	delete []game;
}

Tetris::Tetris(const Tetris& other) {
	game = NULL;
	width = 0;
	heights = {};
	*this = other;
}

Tetris &Tetris::operator=(const Tetris& other) {
	if(this==&other) return *this;

	for(int i = 0; i < width; i++) delete []game[i];
	delete []game;

	build(other.width);

	for(int i = 0;i < width; i++) {
		int altura = other.heights[i];
		heights[i] = altura;
		game[i] = new char[altura];
		for(int j = 0; j < altura; j++) game[i][j] = other.game[i][j];
	}
	return *this;
}

void Tetris::rotateCW(char piece[4][5]) {
	//deve rodar a figura e desloca-la para o mais proximo possivel de 0,0
	char temp[4][5];
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			temp[j][i] = piece[3-i][j];

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++) piece[i][j] = ' ';

	//encontra as menores coordenadas (l,c) do bounding-box
	//da piece
	int l = 10, c = 10;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			if(temp[i][j] != ' ') {
				l = std::min(l, i);
				c = std::min(c, j);
			}

	//translada a piece de modo que ela fique "encostando"
	//nos eixos x,y...
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			if(i+l < 4 && j+c < 4)
				piece[i][j] = temp[i+l][j+c];
}

bool Tetris::ableToAddPiece(const int linhaMinimaInserir, const char piece[4][5], const int posicao) const {
	for(int c = 0; c < 4; c++) {
		for(int l = 0; l < 4; l++) {
			if(piece[l][c] == ' ') continue;
			//verifique se l,c colide com o game...
			int lJogo = linhaMinimaInserir - l;
			int cJogo = c+posicao;
			if(lJogo < 0 || cJogo < 0 || cJogo >= getColumnsNum()) return false;
			if(lJogo < heights[cJogo] && game[cJogo][lJogo] != ' ') return false;

		}
	}
	return true;
}

bool Tetris::addPiece(const int posicao, const int altura, const char piece[4][5]) {
	int linhaMinimaInserir = altura; //temos que comecar em uma posicao acima da altura maxima..
	if(!ableToAddPiece(linhaMinimaInserir, piece, posicao)) {
		return false; //a insercao da piece falhou!
	}


	//insere a piece...
	for(int c = 0; c < 4; c++) {
		int cJogo = c+posicao; //col do game onde iremos inserir a col atual da piece..
		if(cJogo >= getColumnsNum()) continue;
		int novaAlturaMaximaColuna = heights[cJogo];

		bool temPecaAdicionar = false;
		for(int l = 0; l < 4; l++) {
			if(piece[l][c] == ' ') continue;
			temPecaAdicionar = true;
			//verifique se l,c colide com o game...
			int lJogo = linhaMinimaInserir - l;
			if(lJogo+1 > novaAlturaMaximaColuna) novaAlturaMaximaColuna = lJogo+1;
		}
		if(!temPecaAdicionar) continue;

		char *novaColunaJogo = new char[novaAlturaMaximaColuna];
		for(int i = 0; i < novaAlturaMaximaColuna; i++) novaColunaJogo[i] = ' ';
		for(int i = 0; i < heights[cJogo]; i++) novaColunaJogo[i] = game[cJogo][i];

		heights[cJogo] = novaAlturaMaximaColuna;

		for(int l = 0; l < 4; l++) {
			if(piece[l][c] == ' ') continue;
			//verifique se l,c colide com o game...
			int lJogo = linhaMinimaInserir - l;
			novaColunaJogo[lJogo] = piece[l][c];
		}

		delete []game[cJogo];
		game[cJogo] = novaColunaJogo;
	}
	return true;
}

bool Tetris::addPiece(const int posicao, const int altura, const char id, const int rotacao) {
	//implementacao simples, mas nao a mais eficiente...
	const static char pecas[7][4][5] = {
		{
			"I   ",
			"I   ",
			"I   ",
			"I   "
		}, {
			"JJJJ",
			"   J",
			"    ",
			"    "
		}, {
			"LLLL",
			"L   ",
			"    ",
			"    "
		}, {
			"OO  ",
			"OO  ",
			"    ",
			"    "
		}, {
			" SS ",
			"SS  ",
			"    ",
			"    "
		}, {
			"TTT ",
			" T  ",
			"    ",
			"    "
		}, {
			"ZZ  ",
			" ZZ ",
			"    ",
			"    "
		}
	};
	char posPeca[256];
	posPeca['I'] = 0;
	posPeca['J'] = 1;
	posPeca['L'] = 2;
	posPeca['O'] = 3;
	posPeca['S'] = 4;
	posPeca['T'] = 5;
	posPeca['Z'] = 6;

	char piece[4][5] = {0};
	for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) piece[i][j] = pecas[posPeca[id]][i][j];

	int numRotate = rotacao/90;
	for(int i = 0; i < numRotate; i++)
		rotateCW(piece);

	return addPiece(posicao,altura, piece);
}

char Tetris::get(const int col, const int row) const {
	if(row < 0 || row >= heights[col] || col >= width || col<0)
		return ' ';
	return game[col][row];
}