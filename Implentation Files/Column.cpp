#include "Column.h"

Column::Column() : MAX_GAME_PIECES(6)
{
}

Column::Column(int whichColumn) : MAX_GAME_PIECES(6), whichColumn(whichColumn){
}

int Column::getColumnNumber() const{
	return whichColumn;
}

void Column::addGamePiece(const GamePiece &piece){
	if (pieces.size() == MAX_GAME_PIECES)
		throw std::exception("Column is Full. Cannot add anymore game pieces.");
	pieces.push_back(piece);
}

bool Column::columnIsFull() const{
	return pieces.size() == MAX_GAME_PIECES;
}

bool Column::isFourInRow(char gamePiece) const {
	int numMatches = 0;
	auto it = --pieces.end();

	while (gamePiece == it->getSymbol() and it != pieces.begin())
		numMatches++, it--;
	
	/*for (int i = pieces.size() - 1; i >= 0; i--) 
		if (gamePiece == pieces[i].getSymbol())
			numMatches++;*/
	
	return numMatches == 4;
}

int Column::numGamePieces() const{
	return pieces.size();
}

void Column::flickerGamePieces(){
	auto createrFlicker = [](const GamePiece &p, char symbol) {
		p.gotoxy(p.getX(), p.getY());
		std::cout << symbol;
	};

	for (size_t i = 0; i < 3; i++){

		for (size_t k = pieces.size() - 1; k >= (pieces.size() - 4); k--)
			createrFlicker(pieces[i], ' ');
		
		Sleep(150);

		for (size_t j = pieces.size() - 1; j >= (pieces.size() - 4); j--)
			createrFlicker(pieces[i], pieces[i].getSymbol());
	}
}

std::ostream & operator<<(std::ostream &os, Column &c){
	for (auto &piece : c.pieces)
		std::cout << piece;
	return os;
}
