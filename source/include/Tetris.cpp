//	Adapted from Tetris game developed by Salles Viana (https://github.com/sallesviana)
#include "Tetris.h"
#include <iostream>

Tetris::Tetris(const int width) {
	build(width);
}

void Tetris::build(const int width) {
	game = new char*[width];
	heights.resize(width, 0);
	for(int i = 0; i < width; i++) {
		game[i] = NULL;
	}
	this->width = width;
}

int Tetris::getHeight() const {
	return *max_element(begin(heights), end(heights));
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

int Tetris::getWidth() const {
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
		int height = other.heights[i];
		heights[i] = height;
		game[i] = new char[height];
		for(int j = 0; j < height; j++) game[i][j] = other.game[i][j];
	}
	return *this;
}

void Tetris::rotateCW(vector<string>& piece) {
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
				l = min(l, i);
				c = min(c, j);
			}

	//translada a piece de modo que ela fique "encostando"
	//nos eixos x,y...
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			if(i+l < 4 && j+c < 4)
				piece[i][j] = temp[i+l][j+c];
}

bool Tetris::ableToAddPiece(const int linhaMinimaInserir, const vector<string>& piece, const int pos) const {
	for(int c = 0; c < 4; c++) {
		for(int l = 0; l < 4; l++) {
			if(piece[l][c] == ' ') continue;
			//verifique se l,c colide com o game...
			int lJogo = linhaMinimaInserir - l;
			int cJogo = c+pos;
			if(lJogo < 0 || cJogo < 0 || cJogo >= getWidth()) return false;
			if(lJogo < heights[cJogo] && game[cJogo][lJogo] != ' ') return false;

		}
	}
	return true;
}

bool Tetris::addPiece(const int pos, const int height, const vector<string>& piece) {
	int linhaMinimaInserir = height; //temos que comecar em uma pos acima da height maxima..
	if(!ableToAddPiece(linhaMinimaInserir, piece, pos)) {
		return false; //a insercao da piece falhou!
	}


	//insere a piece...
	for(int c = 0; c < 4; c++) {
		int cJogo = c+pos; //col do game onde iremos inserir a col atual da piece..
		if(cJogo >= getWidth()) continue;
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

bool Tetris::addPiece(const int pos, const int height, const char id, const int rot) {
	//implementacao simples, mas nao a mais eficiente...
	const static vector<vector<string>> pieces = {
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
	vector<char> posPiece(256);
	posPiece['I'] = 0;
	posPiece['J'] = 1;
	posPiece['L'] = 2;
	posPiece['O'] = 3;
	posPiece['S'] = 4;
	posPiece['T'] = 5;
	posPiece['Z'] = 6;

	vector<string> piece = pieces[posPiece[id]];

	const int numRotate = rot/90;
	for(int i = 0; i < numRotate; i++) {
		rotateCW(piece);
	}

	return addPiece(pos, height, piece);
}

char Tetris::get(const int col, const int row) const {
	if(row < 0 || row >= heights[col] || col >= width || col<0)
		return ' ';
	return game[col][row];
}