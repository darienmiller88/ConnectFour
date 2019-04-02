#pragma once
#include <iostream>
#include <Windows.h>

class GamePiece{
	public:
		GamePiece(char symbol, int x, int y);
		char getSymbol() const;
		int getX() const;
		int getY() const;
		static int getTotalGamePieces();
		static void gotoxy(int x, int y);
		friend std::ostream &operator << (std::ostream &os, GamePiece &c);
	private:
		char symbol;
		int x;
		int y;
		static int numGamePieces;
};

