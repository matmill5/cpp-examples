// CS1_Lab04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

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
private:
	color c;
	rank r;
};

class Board {
public:
	Board();
	//bool makeMove(std::string, char);
	std::ostream& debugPrint(std::ostream& out);
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
	Board b;

	b.debugPrint(std::cout);

    //std::cout << "Hello World!\n"; 
}