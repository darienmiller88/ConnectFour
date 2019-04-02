#include "GamePiece.h"

int GamePiece::numGamePieces = 0;

GamePiece::GamePiece(char symbol, int x, int y) : symbol(symbol), x(x), y(y) {
	numGamePieces++;
}

char GamePiece::getSymbol() const{
	return symbol;
}

int GamePiece::getX() const{
	return x;
}

int GamePiece::getY() const{
	return y;
}

int GamePiece::getTotalGamePieces() {
	return numGamePieces;
}

void GamePiece::gotoxy(int x, int y){
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

std::ostream & operator<<(std::ostream &os, GamePiece &c){
	c.gotoxy(c.getX(), c.getY());
	std::cout << c.getSymbol();

	return os;
}
