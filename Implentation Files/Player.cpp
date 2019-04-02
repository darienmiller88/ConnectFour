#include "Player.h"


Player::Player(const std::string &name, char symbol) : name(name), gamePieceSymbol(symbol){
}

std::string Player::getName() const{
	return name;
}

char Player::getGamePieceSymbol() const{
	return gamePieceSymbol;
}
