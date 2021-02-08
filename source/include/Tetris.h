#ifndef TETRIS_H
#define TETRIS_H

#include <vector>
#include <algorithm>

using namespace std;

class Tetris {
	private:
		char **game;
		vector<int> heights;
		int width;

		bool isRowComplete(const int) const;
		void removeRow(const int);
		void build(const int);
		void rotateCW(char[4][5]);
		bool ableToAddPiece(const int, const char[4][5], const int) const;
		bool addPiece(const int, const int, const char[4][5]);
	public:
		Tetris() { };
		Tetris(const int);
		Tetris(const Tetris&);
		~Tetris();

		Tetris &operator=(const Tetris&);

		void removeRows();
		void removeColumns(const int);
		char get(const int, const int) const;
		int getWidth() const;
		int getHeight() const;
		int getHeight(const int c) const { return heights[c]; }
		bool addPiece(const int, const int, const char, const int);
};

#endif