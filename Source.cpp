#include <iostream>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <string>
#include "Column.h"
#include <unordered_map>
using namespace std;

const int NUM_COLUMNS = 7;//seven columns in connect four
const int NUM_ROWS = 6;//six rows in connect four
const int COLUMN_DISTANCE = 8;//the distance between the midpoints of each column
const int ROW_DISTANCE = 3;//the distance between the midpoints of each row
const int YPOS = 2;//how far down the cursor will be
const int HOW_FAR_DOWN = 5;//how far down the board will be

void gotoxy(int x, int y);
void drawBoard();
void createCursor(int xPos, int yPos, char cursorSegmentOne, char cursorSegmentTwo, char cursorHead);
int selectColumn(const vector<Column> &columns);
void resetCursor();
void setGamePieces(Column &column, const vector<int> &columnYCoordinates, char userGamePiece);
void playGame();
void findXAndYCoordinates(vector<int> &columnYCoordinates, vector<int> &columnXCoordinates);
bool isFourInRow(const vector<Column> &columns, char gamePiece, const Column &column);

int main(){
	
	playGame();
	//setGamePieces(columnOfChoice);
	
}

void playGame(){
	vector<int> columnXCoordinates;//coordinates for the midpoint of each column 
	vector<int> columnYCoordinates;//coordinates for the midpoint of each row 
	findXAndYCoordinates(columnYCoordinates, columnXCoordinates);
	bool gameIsOver = false;
	vector<Column> columns(columnXCoordinates.begin(), columnXCoordinates.end());
	string nameOne, nameTwo;
	pair<string, char> winner;
	Column c;

	cout << "Player one, enter your name!: ";
	cin >> nameOne;

	cout << "Player two, enter your name!: ";
	cin >> nameTwo;

	unordered_map<string, char> players{ {nameOne, 'o'}, {nameTwo, 'x'} };
	system("cls");
	drawBoard();
	while(!gameIsOver){
		for (auto it = players.begin(); it != players.end() and !gameIsOver; it++) {
			gotoxy(0, 0);
			cout << it->first << ", it's your turn!";
			const int COLUMN_OF_CHOICE = selectColumn(columns);
			setGamePieces(columns[COLUMN_OF_CHOICE], columnYCoordinates, it->second);
			gameIsOver = columns[COLUMN_OF_CHOICE].isFourInRow(it->second);
			winner = *it;

			for (auto &column : columns)
				cout << column;
			resetCursor();
		}
	}
	

	cout << winner.first << " won!\n";
}

void findXAndYCoordinates(vector<int> &columnYCoordinates, vector<int> &columnXCoordinates){
	//push the coordinate of the first row into the vector. This will let us know where, in relation
	//to the gameboard, the following midpoints for each row exists.
	columnYCoordinates.push_back(HOW_FAR_DOWN + 1);

	//use the previous index of the vector to find the next one by adding the row distance between the 
	//midpoint of each row.
	for (int i = 0; i < NUM_ROWS - 1; ++i)
		columnYCoordinates.push_back(columnYCoordinates[i] + ROW_DISTANCE);

	//push the coordinate of the midpoint of the first column into the vector. This will let us know where, 
	//in relation to the gameboard, the following midpoints for each column exists.
	columnXCoordinates.push_back(COLUMN_DISTANCE / 2);

	//use the previous index of the vector to find the next one by adding the column distance between the 
	//midpoint of each column.
	for (int i = 0; i < NUM_COLUMNS - 1; ++i)
		columnXCoordinates.push_back(columnXCoordinates[i] + COLUMN_DISTANCE);	
}

bool isFourInRow(const vector<Column> &columns, char gamePiece, const Column &column){
	
	
	return column.isFourInRow(gamePiece);
}

void drawBoard(){
	//cout << "To control cursor, press left or right arrow key. Press enter to select your column of choice.\n";

	for (int i = 0; i < HOW_FAR_DOWN; ++i)
		cout << "\n";

	for (int i = 1; i <= NUM_ROWS * 3; ++i){
		for (int j = 0; j < NUM_COLUMNS; ++j)
			 (i % 3 == 0) ? cout << "|_______" : cout << "|\t";
		cout << "|\n";
	}

	//print out the number labeling each column
	for (int i = 0; i < 7; ++i)
		cout << setw(5) << i + 1 << "\t";
}

void createCursor(int xPos, int yPos, char cursorSegmentOne, char cursorSegmentTwo, char cursorHead){
	gotoxy(xPos, yPos);
	cout << cursorSegmentOne;
	gotoxy(xPos, yPos + 1);
	cout << cursorSegmentTwo;
	gotoxy(xPos, yPos + 2);
	cout << cursorHead;
	resetCursor();
}

int selectColumn(const vector<Column> &columns){
	//left, right and enter keys are assigned their respective ascii code representation. 
	enum keyCode { ENTER = 13, LEFT = 75, RIGHT = 77 };
	char input = ' ';
	const char cursorSegmentOne = '|', cursorSegmentTwo = '|', cursorHead = 'v';
	const int FIRST_COL = columns.front().getColumnNumber(), LAST_COL = columns.back().getColumnNumber();
	static int xPos = FIRST_COL, columnOfChoice = 0;
	
	while(input != ENTER){
		createCursor(xPos, YPOS, cursorSegmentOne, cursorSegmentTwo, cursorHead);
		input = _getch();
		createCursor(xPos, YPOS, ' ', ' ', ' ');
	
		if (input == LEFT && xPos == FIRST_COL)
			xPos = LAST_COL, columnOfChoice = NUM_COLUMNS - 1;
		else if (input == RIGHT && xPos == LAST_COL)
			xPos = FIRST_COL, columnOfChoice = 0;
		else if (input == RIGHT && xPos >= FIRST_COL && xPos < LAST_COL)
			xPos += COLUMN_DISTANCE, columnOfChoice++;
		else if (input == LEFT && xPos > FIRST_COL && xPos <= LAST_COL)
			xPos -= COLUMN_DISTANCE, columnOfChoice--;
		else if (input == ENTER && columns[columnOfChoice].columnIsFull())
			input = ' ';
	}
	resetCursor();

	return columnOfChoice;
}

void resetCursor(){
	gotoxy(0, HOW_FAR_DOWN + (NUM_ROWS * 3));
}

void setGamePieces(Column &column, const vector<int> &columnYCoordinates, char userGamePiece){
	const int ROW_INDEX = NUM_ROWS - column.numGamePieces() - 1;
	
	try{
		column.addGamePiece(GamePiece(userGamePiece, column.getColumnNumber(), columnYCoordinates[ROW_INDEX]));
	}catch (const exception &e){
		cout << e.what() << endl;
	}
}

void gotoxy(int x, int y)
{
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}