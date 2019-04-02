#pragma once
#include <string>

class Player{
	public:
		Player(const std::string &name, char symbol);
		std::string getName() const;
		char getGamePieceSymbol() const;
	private:
		std::string name;
		char gamePieceSymbol;
};

