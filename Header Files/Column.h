#pragma once
#include <iostream>
#include <vector>
#include <exception>
#include "GamePiece.h"

class Column{
	public:
		Column();
		Column(int whichColumn);
		int getColumnNumber() const;
		void addGamePiece(const GamePiece &piece);
		bool columnIsFull() const;
		bool isFourInRow(char gamePiece) const;
		int numGamePieces() const;
		void flickerGamePieces();
		friend std::ostream &operator << (std::ostream &os, Column &c);
	private:
		std::vector<GamePiece> pieces;
		const int MAX_GAME_PIECES;
		int whichColumn;
};

