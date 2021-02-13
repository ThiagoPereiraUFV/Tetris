//	Adapted from Tetris game developed by Salles Viana (https://github.com/sallesviana)
#ifndef TETRIS_H
#define TETRIS_H

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Tetris {
	private:
		vector<string> game;
		vector<int> heights;
		int width;

		bool isRowComplete(const int) const;
		void removeRow();
		void build(const int);
		void rotateCW(vector<string>&);
		bool ableToAddPiece(const int, const vector<string>&, const int) const;
		bool addPiece(const int, const int, const vector<string>&);
	public:
		Tetris() { };
		Tetris(const int);
		Tetris(const Tetris&);

		Tetris& operator=(const Tetris&);

		int removeRows();
		char get(const int, const int) const;
		int getWidth() const;
		int getMaxHeight() const;
		int getHeight(const int c) const { return heights[c]; }
		bool addPiece(const int, const int, const char, const int);
};

#endif