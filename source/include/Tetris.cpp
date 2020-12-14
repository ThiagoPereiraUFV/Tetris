#include "Tetris.h"
#include <iostream>

Tetris::Tetris(int largura) {
	constroi(largura);
}

void Tetris::constroi(int largura) {
	jogo = new char*[largura];
	alturas = new int[largura];
	for(int i = 0; i < largura; i++) {
		jogo[i] = NULL;
		alturas[i] = 0;
	}
	this->largura = largura;
}

#include <cstdlib>
int Tetris::getAltura() const {
	int mx = 0;
	for(int i = 0; i < largura; i++) mx = std::max(mx, alturas[i]);
	return mx;
}

void Tetris::removeColuna(int col) {
	delete []jogo[col];
	char **novoJogo = new char*[largura-1];
	int * novaAlturas = new int[largura-1];
	for(int i = 0; i < col; i++) {
		novoJogo[i] = jogo[i];
		novaAlturas[i] =alturas[i];
	}
	for(int i = col+1; i < largura; i++) {
		novoJogo[i-1] = jogo[i];
		novaAlturas[i-1] =alturas[i];
	}
	delete []jogo;
	jogo = novoJogo;
	delete []alturas;
	alturas = novaAlturas;
	largura--;

}


bool Tetris::linhaEstaCompleta(int l) const {
	for(int i = 0; i < largura; i++) {
		if(l >= alturas[i] || jogo[i][l] == ' ') return false;
	}
	return true;
}

#include <cassert>
void Tetris::removeLinhaCompleta(int l) {
	for(int i = 0; i < largura; i++) {
		assert(l < alturas[i]);
		char *newColumn;
		if(alturas[i] == 1) {
			newColumn = NULL;
		} else newColumn = new char[alturas[i]-1];

		for(int j = 0; j < l; j++) newColumn[j] = jogo[i][j];
		for(int j = l+1; j < alturas[i]; j++) newColumn[j-1] = jogo[i][j];

		delete []jogo[i];
		jogo[i] = newColumn;
		alturas[i]--;

		int alturaMaximaNewColumn = 0;
		for(int j = 0; j < alturas[i]; j++) {
			if(newColumn[j] != ' ') alturaMaximaNewColumn = j+1;
		}
		if(alturaMaximaNewColumn != alturas[i]) {
			//devido a uma remocao precisamos deixar essa coluna mais justa!
			char *newNewColumn = new char[alturaMaximaNewColumn];
			alturas[i] = alturaMaximaNewColumn;
			for(int j = 0; j < alturaMaximaNewColumn; j++) newNewColumn[j] = newColumn[j];
			delete []jogo[i];
			jogo[i] = newNewColumn;
		}
	}
}

void Tetris::removeLinhasCompletas() {
	int alturaMaxima = getAltura();
	for(int i = 0; i < alturaMaxima; i++) {
		if(linhaEstaCompleta(i)) {
			removeLinhaCompleta(i);
			alturaMaxima--; //uma linha foi removida!
			i--; //para testar a mesma linha denovo (ja que tabuleiro foi deslocado para baixo...)
		}
	}
}

int Tetris::getNumColunas() const {
	return largura;
}

Tetris::~Tetris() {
	delete [] alturas;
	for(int i = 0; i < largura; i++) delete []jogo[i];
	delete []jogo;
}

Tetris::Tetris(const Tetris &other) {
	jogo = NULL;
	largura = 0;
	alturas = NULL;
	*this = other;
}

Tetris &Tetris::operator=(const Tetris &other) {
	if(this==&other) return *this;

	delete [] alturas;
	for(int i = 0; i < largura; i++) delete []jogo[i];
	delete []jogo;

	constroi(other.largura);

	for(int i = 0;i < largura; i++) {
		int altura = other.alturas[i];
		alturas[i] = altura;
		jogo[i] = new char[altura];
		for(int j = 0; j < altura; j++) jogo[i][j] = other.jogo[i][j];
	}
	return *this;
}

void Tetris::rotateCW(char peca[4][5]) {
	//deve rodar a figura e desloca-la para o mais proximo possivel de 0,0
	char temp[4][5];
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			temp[j][i] = peca[3-i][j];

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++) peca[i][j] = ' ';

	//encontra as menores coordenadas (l,c) do bounding-box
	//da peca
	int l = 10, c = 10;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			if(temp[i][j] != ' ') {
				l = std::min(l, i);
				c = std::min(c, j);
			}

	//translada a peca de modo que ela fique "encostando"
	//nos eixos x,y...
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			if(i+l < 4 && j+c < 4)
				peca[i][j] = temp[i+l][j+c];


}

void imprimePeca(int rotacoes, const char peca[4][5]) {
	int response = system("clear");
	std::cout << "Rotacoes: " << rotacoes << std::endl;
	for(int i = 0; i < 4; i++)
		std::cout << peca[i] << std::endl;
	response = system("sleep 0.9");
}

bool Tetris::podeInserirPeca(int linhaMinimaInserir, const char peca[4][5], int posicao) const {
	for(int c = 0; c < 4; c++) {
		for(int l = 0; l < 4; l++) {
			if(peca[l][c] == ' ') continue;
			//verifique se l,c colide com o jogo...
			int lJogo = linhaMinimaInserir - l;
			int cJogo = c+posicao;
			if(lJogo < 0 || cJogo < 0 || cJogo >= getNumColunas()) return false;
			if(lJogo < alturas[cJogo] && jogo[cJogo][lJogo] != ' ') return false;

		}
	}
	return true;
}

bool Tetris::adicionaForma(int posicao, int altura, const char peca[4][5]) {
	int linhaMinimaInserir = altura; //temos que comecar em uma posicao acima da altura maxima..
	if(!podeInserirPeca(linhaMinimaInserir, peca, posicao)) {
		return false; //a insercao da peca falhou!
	}


	//insere a peca...
	for(int c = 0; c < 4; c++) {
		int cJogo = c+posicao; //coluna do jogo onde iremos inserir a coluna atual da peca..
		if(cJogo >= getNumColunas()) continue;
		int novaAlturaMaximaColuna = alturas[cJogo];

		bool temPecaAdicionar = false;
		for(int l = 0; l < 4; l++) {
			if(peca[l][c] == ' ') continue;
			temPecaAdicionar = true;
			//verifique se l,c colide com o jogo...
			int lJogo = linhaMinimaInserir - l;
			if(lJogo+1 > novaAlturaMaximaColuna) novaAlturaMaximaColuna = lJogo+1;
		}
		if(!temPecaAdicionar) continue;

		char *novaColunaJogo = new char[novaAlturaMaximaColuna];
		for(int i = 0; i < novaAlturaMaximaColuna; i++) novaColunaJogo[i] = ' ';
		for(int i = 0; i < alturas[cJogo]; i++) novaColunaJogo[i] = jogo[cJogo][i];

		alturas[cJogo] = novaAlturaMaximaColuna;

		for(int l = 0; l < 4; l++) {
			if(peca[l][c] == ' ') continue;
			//verifique se l,c colide com o jogo...
			int lJogo = linhaMinimaInserir - l;
			novaColunaJogo[lJogo] = peca[l][c];
		}

		delete []jogo[cJogo];
		jogo[cJogo] = novaColunaJogo;
	}
	return true;
}

bool Tetris::adicionaForma(int posicao, int altura, char id, int rotacao) {
	//implementacao simples, mas nao a mais eficiente...
	const static char pecas[7][4][5] = { {
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

	char peca[4][5] = {0};
	for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) peca[i][j] = pecas[posPeca[id]][i][j];

	int numRotate = rotacao/90;
	for(int i = 0; i < numRotate; i++)
		rotateCW(peca);

	return adicionaForma(posicao,altura, peca);
}

char Tetris::get(int coluna, int linha) const {
	if(linha < 0 || linha >= alturas[coluna] || coluna >= largura || coluna<0)
		return ' ';
	return jogo[coluna][linha];
}

std::ostream &operator<<(std::ostream &out, const Tetris &t) {
	int maxHeight = t.getAltura();

	//out << " ";
	//for(int j=0;j<t.getNumColunas();j++) out << "-";
	//out << "\n";

	for(int i = maxHeight-1; i >= 0; i--) {
		out << "|";
		for(int j = 0; j < t.getNumColunas(); j++) {
			if(i >= t.alturas[j]) out << " ";
			else out << t.jogo[j][i];
		}
		out << "|\n";
	}

	out << " ";
	for(int j = 0; j < t.getNumColunas(); j++) out << "-";
	out << "\n";

	return out;
}
