// CS1_Lab04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

enum color {      // value as int EMPTY==0 RED==1 BLACK==2
	EMPTY, RED, BLACK
};
enum rank {    // value as int NOTKING==0 KING==1
	NOTKING, KING
};

class Square {
public:
	Square();
	bool isEmpty();
	void setEmpty();
	bool setSquare(color, rank);
	color getColor();
	rank getRank();
	char displaySqrColor();
private:
	color c;
	rank r;
};

class Board {
public:
	Board();
	//bool makeMove(std::string, char);
	std::ostream& debugPrint(std::ostream& out);
	void displayBoard();
	void SetupBoard(std::string fileName);
	bool SaveGame(std::string fileName);
private:
	Square arr[8][8];
	//bool validMove();
	//bool removeCaptured();
	//bool makeKing();
};

Board::Board() {
	for (int i = 0; i < 8; i++) {
		for (int z = 0; z < 8; z++) {
			Square s;
			arr[i][z] = s;
		}
	}
}

std::ostream& Board::debugPrint(std::ostream& out) {
	for (int i = 0; i < 8; i++) {
		out << '|';
		for (int z = 0; z < 8; z++) {
			out << arr[i][z].getColor() << '|';
		}
		out << '\n' ;
	}
	return out;
}
Square::Square() {
	this->c = EMPTY;
	this->r = NOTKING;
	return;
}
bool Square::isEmpty() {
	return (this->c == EMPTY);
}
void Square::setEmpty() {
	this->c = EMPTY;
}
bool Square::setSquare(color c, rank r) {
	this->c = c;
	this->r = r;
	return 0;
}
color Square::getColor() {
	return c;
}
rank Square::getRank() {
	return r;
}
bool makeMove(std::string m, char d) {
	return 0;
}
bool validMove() {
	return 0;
}
bool removeCaptured() {
	return 0;
}
bool makeKing() {
	return 0;
}
char Square::displaySqrColor() {
	if (this->c == 1) {
		return 'R';
	}
	if (this->c == 2) {
		return 'B';
	}
	if (this->c == 0) {
		return 0;
	}
}

//
//  DisplayBoard function for Board class 
//


// This function is provided for you
//
// display an 8x8 board of squares like the following:
//
//  +-----+-----+-----+-----+...
//  |*****|     |*****|     |
//  |*****|  x  |*****|  x  |
//  |*****|     |*****|     |
//  +-----+-----+-----+-----+...
//
//   where the square with the x in it is a black square where the x indicates the color (empty, R or B) 
//   and the white squares are all stars; 

void Board::displayBoard() {
	std::string dashes = "+-----";      //characters for square top and bottom bounds
	std::string whiteSquareFill = "|*****";      //fill for white squares
	std::string blackSquareFill = "|     ";       // fill for black squares
	std::string line = "";
	std::string filler;
	int i, j, color;
	int boardSize = 8;

	for (i = 0; i < boardSize; i++) {   //repeat 8 times, once for each row of squares 

		line = "";
		for (j = 0; j < boardSize; j++) {     //build line of cells for boundary  ( +---+ )
			line = line + dashes;
		}
		std::cout << line << "+" << std::endl;

		color = (i + 1) % 2;          // Mod 2 - needed to distinguish rows starting with white or black squares
									// color = 1 ->row starts with white square, color = 0 -> start with black square

		line = "";
		for (j = 0; j < boardSize; j++) {           //build first line for row of square
			if ((j + color) % 2) {
				filler = whiteSquareFill;        // fill stars for white squares    ( |*****|)
			}
			else {
				filler = blackSquareFill;        // fill spaces for black squares     ( |    |)
			}
			line = line + filler;
		}

		std::cout << line << "|" << std::endl;


		line = "";
		for (j = 0; j < boardSize; j++) {          //build second line for row of square ( |  x  | )
			if ((j + color) % 2) {
				filler = whiteSquareFill;        // fill with stars for white squares    ( |*****|)
			}
			else {
				filler = "|  ";                  // fill spaces for blacksquares
				filler += arr[i][j].displaySqrColor();   // display color of checker
				filler += "  ";
			}
			line = line + filler;
		}
		std::cout << line << "|" << std::endl;

		line = "";
		for (j = 0; j < boardSize; j++) {           //build third line for row of square 
			if ((j + color) % 2) {
				filler = whiteSquareFill;        // fill with stars for white squares   ( |*****| )
			}
			else {
				filler = blackSquareFill;        // fill with spaces for black squares   ( |     | )
			}
			line = line + filler;
		}
		std::cout << line << "|" << std::endl;
	}


	line = "";
	for (j = 0; j < boardSize; j++) {     //build line of cells for boundary on bottom of board   ( +---+ )
		line = line + dashes;
	}
	std::cout << line << "+" << std::endl;

	std::cout << std::endl;

}
void Board::SetupBoard(std::string fileName) {
	std::ifstream input_file(fileName);
	if (!input_file.is_open()) {
		std::cout << "Error opening file";
	}
	char str[256];
	while (!input_file.eof()) {
		input_file.getline(str, 256, '\n');
		arr[str[0] - '0'][str[2] - '0'].setSquare(color(str[4] - '0'), rank(str[6] - '0'));
	}
	input_file.close();
}
bool Board::SaveGame(std::string fileName) {
	std::ifstream file_exists_check(fileName);
	if (file_exists_check.is_open()) {
			char users_overwrite_dec;
			std::cout << "File already exists, would you like to overwrite (Y:N): ";
			std::cin >> users_overwrite_dec;
			if (users_overwrite_dec == 'Y') {
				std::ofstream output_file(fileName);
				for (int i = 0; i < 8; i++) {
					for (int z = 0; z < 8; z++) {
						output_file << i << " " << z << " " << arr[i][z].getColor() << " " << arr[i][z].getRank() << '\n';
					}
				}
				output_file.close();
				return 1;
			}
			else {
				std::cout << "Game not saved" << '\n';
				file_exists_check.close();
				return 0;
			}
	}
	std::ofstream output_file(fileName);
	for (int i = 0; i < 8; i++) {
		for (int z = 0; z < 8; z++) {
			output_file << i << " " << z << " " << arr[i][z].getColor() << " " << arr[i][z].getRank() << '\n';
		}
	}
	output_file.close();
	return 1;
}

int main()
{
	//===========TEST SQUARE===============
	Square testSquare;

	// simple test if constructor set rank to NOTKING
	if (testSquare.getRank() == NOTKING)
		std::cout << "Test Passed - ";
	else
		std::cout << "Test Failed - ";

	std::cout << "Value of rank for testSquare: " << testSquare.getRank() << std::endl;

	// simple test if constructor set color to EMPTY
	if (testSquare.getColor() == EMPTY)
		std::cout << "Test Passed - ";
	else
		std::cout << "Test Failed - ";

	std::cout << "Value of color for testSquare: " << testSquare.getColor() << std::endl;
	
	std::cout << '\n';

	Board c;

	std::cout << "Enter N to start a new game or S to start a saved game: ";
	char user_input;
	std::cin >> user_input;

	if (user_input == 'N') {
		c.SetupBoard("newgame.txt");
		c.displayBoard();
	}
	if (user_input == 'S') {
		std::string users_saved_game;
		std::cout << "Enter the file name and extension of the saved game: ";
		std::cin >> users_saved_game;
		c.SetupBoard(users_saved_game);
		c.displayBoard();
	}
	else {
		std::cout << "No matching input";
	}

	std::cout << "Enter Q to quit the game and save to file: ";

	char user_input_quit;
	std::cin >> user_input_quit;

	if (user_input_quit == 'Q') {
		bool fileWriteTest;
		std::string users_fileName;
		std::cout << "Enter the filename and extension to save the game: ";
		std::cin >> users_fileName;
		fileWriteTest = c.SaveGame(users_fileName);
		if (fileWriteTest == 1) {
			std::cout << "Saved game to file";
		}
	}
    //std::cout << "Hello World!\n"; 
}
