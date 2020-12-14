#ifndef TETRIS_H
#define TETRIS_H

#include <ostream>

class Tetris {
	public:
		Tetris(int largura);
		Tetris() { };
		friend std::ostream &operator<<(std::ostream &, const Tetris&);

		void removeColuna(int col);
		void removeLinhasCompletas();
		int getNumColunas() const;
		int getAltura() const;
		int getAltura(int c) const {return alturas[c];}
		bool adicionaForma(int posicao, int altura, char id, int rotacao);
		char get(int coluna, int linha) const;

		~Tetris();
		Tetris(const Tetris &);
		Tetris &operator=(const Tetris &);
	private:
		char **jogo;
		int *alturas;
		int largura;

		bool linhaEstaCompleta(int i) const;
		void removeLinhaCompleta(int i);
		void constroi(int largura);
		void rotateCW(char peca[4][5]);
		bool podeInserirPeca(int linhaMinimaInserir, const char peca[4][5], int posicao) const;
		bool adicionaForma(int posicao, int altura, const char peca[4][5]);
};

#endif
