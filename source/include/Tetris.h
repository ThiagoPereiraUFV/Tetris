#ifndef TETRIS_H
#define TETRIS_H

#include <vector>

using namespace std;

class Tetris {
	private:
		char **game;
		vector<int> heights;
		int width;

		bool isRowComplete(const int) const;
		void removeRow(const int);
		void build(const int);
		void rotateCW(char piece[4][5]);
		bool ableToAddPiece(const int, const char piece[4][5], const int) const;
		bool addPiece(const int, const int, const char piece[4][5]);
	public:
		Tetris(const int);
		Tetris() { };

		void removeColumns(const int);
		void removeRows();
		int getColumnsNum() const;
		int getHeight() const;
		int getHeight(const int c) const { return heights[c]; }
		bool addPiece(const int, const int, const char, const int);
		char get(const int, const int) const;

		~Tetris();
		Tetris(const Tetris &);
		Tetris &operator=(const Tetris&);
};

#endif
