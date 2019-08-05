// CS1_Lab06.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	std::ostream& debugPrint(std::ostream& out);
	void displayBoard();
	void SetupBoard(std::string fileName);
	bool SaveGame(std::string fileName);
	bool MakeMove(std::string command, std::string from, std::string to);
	bool setTurn();
	bool getTurn();
	bool makeKing();
private:
	Square arr[8][8];
	bool validMove(std::string command, std::string from, std::string to);
	Board* executeMove(std::string command, std::string from, std::string to);
	//bool removeCaptured(); //Design doesn't need this...  Creates unneeded complexity.  Feature is included in executeMove()
	bool turn = 0;
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
			out << "(" << i << "," << z << ")";
			if (arr[i][z].getColor() == 1) {
				out << "R" << arr[i][z].getRank();
			}
			else if (arr[i][z].getColor() == 2) {
				out << "B" << arr[i][z].getRank();
			}
			else {
				out << "  ";
			}
			out << '|';
		}
		out << '\n';
	}
	return out;
}
bool Board::MakeMove(std::string command, std::string from, std::string to) {
	if (this->validMove(command, from, to)) {
		executeMove(command, from, to);
		return 1;
	}
	else {
		return 0;
	}
}
Board* Board::executeMove(std::string command, std::string from, std::string to) {
	if (command.compare("mov") == 0) {//make move
		this->arr[to[1] - '0'][to[3] - '0'].setSquare(this->arr[from[1] - '0'][from[3] - '0'].getColor(), this->arr[from[1] - '0'][from[3] - '0'].getRank()); //Set to-square to from-square
		this->arr[from[1] - '0'][from[3] - '0'].setSquare(EMPTY, NOTKING);//reset from-square to default
		return this;
	}
	if (command.compare("jmp") == 0) {//make jump
		this->arr[to[1] - '0'][to[3] - '0'].setSquare(this->arr[from[1] - '0'][from[3] - '0'].getColor(), this->arr[from[1] - '0'][from[3] - '0'].getRank()); //Set to-square to from-square
		this->arr[from[1] - '0'][from[3] - '0'].setSquare(EMPTY, NOTKING);//reset from-square to default
		this->arr[((from[1] - '0') + (to[1] - '0')) / 2][((from[3] - '0') + (to[3] - '0')) / 2].setSquare(EMPTY, NOTKING);
		return this;
	}
	return 0;
}
bool Board::validMove(std::string command, std::string from, std::string to) {
	//Start general check commands
	{//check if command is valid
		if (command.compare("mov") != 0 && command.compare("jmp") != 0) {
			std::cout << "Please enter a valid move command (mov:jmp): " << '\n';
			return 0;
		}
		//check if cordinate is within range
		if (from[0] != '(' || (from[1] - '0') > 8 || (from[1] - '0') < 0 || from[2] != ',' || (from[3] - '0') > 8 || (from[3] - '0') < 0 || from[4] != ')') {
			std::cout << "Please enter a valid 'from' cordinate ('(x,y)'): " << '\n';
			return 0;
		}
		//check if cordinate are within range
		if (to[0] != '(' || (to[1] - '0') > 8 || (to[1] - '0') < 0 || to[2] != ',' || (to[3] - '0') > 8 || (to[3] - '0') < 0 || to[4] != ')') {
			std::cout << "Please enter a valid 'to' cordinate ('(x,y)'): " << '\n';
			return 0;
		}
		//Check if from-space is empty
		if ((this->arr[(from[1] - '0')][(from[3] - '0')]).isEmpty()) {
			std::cout << "Cannot move from (" << from[1] << "," << from[3] << ") because the space is empty" << '\n';
			return 0;
		}
		//Check if to-space is occupied
		if (!(this->arr[(to[1] - '0')][(to[3] - '0')].isEmpty())) {
			std::cout << "Cannot move to (" << to[1] << "," << to[3] << ") because the space is occupied";
			return 0;
		}
	}//End general checks
	//Mov command
	{//Start mov-specific check commands
		if (command == "mov") {
			//NonKing movement specific
			if (this->arr[from[1] - '0'][from[3] - '0'].getRank() == 0) { //Check if notking
				{//BLACK MOVE
					if ((this->arr[from[1] - '0'][from[3] - '0'].getColor() == 2) && this->getTurn() == false) {
						if (((to[1] - '0') - (from[1] - '0') == 1)) { //Check if square's x-cord is within one space
							if (((from[3] - '0') - (to[3] - '0') == 1) || ((to[3] - '0') - (from[3] - '0') == 1)) { //Check if square's y-cord is within one space
								std::cout << "BLACK-turn Move is valid" << '\n';
								return 1;
							}
							else {
								std::cout << "Cannot move, Y cordinate is more than 1 space away" << '\n';
								return 0;
							}
						}
						else {
							std::cout << "Cannot move, X cordinate is more than 1 space away" << '\n';
							return 0;
						}
					}
				}//End non-king mov black
				{//RED MOVE
					if ((this->arr[from[1] - '0'][from[3] - '0'].getColor() == 1) && this->getTurn() == true) {
						if (((from[1] - '0') - (to[1] - '0') == 1)) { //Check if square's x-cord is within one space
							if (((from[3] - '0') - (to[3] - '0') == 1) || ((to[3] - '0') - (from[3] - '0') == 1)) { //Check if square's y-cord is within one space
								std::cout << "RED-Turn Move was successful" << '\n';
								return 1;
							}
							else {
								std::cout << "Cannot move, Y cordinate is more than 1 space away" << '\n';
								return 0;
							}
						}
						else {
							std::cout << "Cannot move, X cordinate is more than 1 space away" << '\n';
							return 0;
						}
					}
					else {
						std::cout << "Not your turn." << '\n';
						return 0;
					}
				}
			}
			{//King movement specific
				if (this->arr[from[1] - '0'][from[3] - '0'].getRank() == 1) {
					if (((from[1] - '0') - (to[1] - '0') == 1) || ((from[1] - '0') - (to[1] - '0') == -1)) { //Check if square's x-cord is within one space
						if (((from[3] - '0') - (to[3] - '0') == 1) || ((to[3] - '0') - (from[3] - '0') == 1)) { //Check if square's y-cord is within one space
							std::cout << "King's Move is valid";
							return 1;
						}
						else {
							std::cout << "Cannot move, Y cordinate is more than 1 space away" << '\n';
							return 0;
						}
					}
					else {
						std::cout << "Cannot move, X cordinate is more than 1 space away" << '\n';
						return 0;
					}
				}
			}//End king movement
		}
	}//End mov check
	//Jump Command
	{//Start jmp-specific check commands
		if (command == "jmp") {
			if (this->arr[from[1] - '0'][from[3] - '0'].getColor() != this->arr[((from[1] - '0') + (to[1] - '0')) / 2][((from[3] - '0') + (to[3] - '0')) / 2].getColor()) {
				{//NonKing jump movement
					if (this->arr[from[1] - '0'][from[3] - '0'].getRank() == 0) { //Check if notking
						//Black jump
						if ((this->arr[from[1] - '0'][from[3] - '0'].getColor() == 2) && this->turn == false) {
							if (((to[1] - '0') - (from[1] - '0') == 2)) { //Check if square's x-cord is within two space
								if (((from[3] - '0') - (to[3] - '0') == 2) || ((to[3] - '0') - (from[3] - '0') == 2)) { //Check if square's y-cord is within one space
									std::cout << "Black-Jump is valid" << '\n';
									return 1;
								}
								else {
									std::cout << "Cannot move, Y cordinate is not 2 spaces away" << '\n';
									return 0;
								}
							}
							else {
								std::cout << "Cannot move, X cordinate is not 2 spaces away" << '\n';
								return 0;
							}
						}
						//Red jump
						if ((this->arr[from[1] - '0'][from[3] - '0'].getColor() == 1) && this->turn == true) {
							if (((to[1] - '0') - (from[1] - '0') == -2)) { //Check if square's x-cord is within two space
								if (((from[3] - '0') - (to[3] - '0') == 2) || ((to[3] - '0') - (from[3] - '0') == 2)) { //Check if square's y-cord is within one space
									std::cout << "Red-Jump is valid" << '\n';
									return 1;
								}
								else {
									std::cout << "Cannot move, Y cordinate is not 2 spaces away" << '\n';
									return 0;
								}
							}
							else {
								std::cout << "Cannot move, X cordinate is not 2 spaces away" << '\n';
								return 0;
							}
						}
						else {
							std::cout << "Not your turn." << "\n";
							return 0;
						}
					}
				}
				//King movement specific
				if (this->arr[from[1] - '0'][from[3] - '0'].getRank() == 1) { //Check if notking
					if (((to[1] - '0') - (from[1] - '0') == 2) || ((from[1] - '0') - (to[1] - '0') == 2)) { //Check if square's x-cord is within two space
						if (((from[3] - '0') - (to[3] - '0') == 2) || ((to[3] - '0') - (from[3] - '0') == 2)) { //Check if square's y-cord is within one space
							std::cout << "King's Jump Move is valid";
							return 1;
						}
						else {
							std::cout << "Cannot move, Y cordinate is not 2 spaces away" << '\n';
							return 0;
						}
					}
					else {
						std::cout << "Cannot move, X cordinate is not 2 spaces away" << '\n';
						return 0;
					}
				}
			}
			else {
				std::cout << "Invalid move, can only jump opposing color";
				return 0;
			}
		}
	}//End of Jump
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
//bool removeCaptured() {
	//Do nothing
	//return 0;
//}
bool Board::makeKing() {
	for (int z = 0; z < 8; z++) {
		if (arr[0][z].getColor() == 1) {
			arr[0][z].setSquare(arr[0][z].getColor(), KING);
		}
	}
	for (int z = 0; z < 8; z++) {
		if (arr[7][z].getColor() == 2) {
			arr[0][z].setSquare(arr[0][z].getColor(), KING);
		}
	}
	return 1;
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
	else {
		std::ofstream output_file(fileName);
		for (int i = 0; i < 8; i++) {
			for (int z = 0; z < 8; z++) {
				output_file << i << " " << z << " " << arr[i][z].getColor() << " " << arr[i][z].getRank() << '\n';
			}
		}
		output_file.close();
		return 1;
	}
}
bool Board::setTurn() {
	this->turn = !this->turn;
	return 1;
}
bool Board::getTurn() {
	return turn;
}

int main()
{
	std::string mov;
	std::string from;
	std::string to;
	char user_input[256];
	Board c;
	std::cout << "Would you like to start a new game or load a saved-game? (N:S): " << '\n';
	std::cin >> user_input;
	if (user_input[0] == 'S') {
		std::cout << "Please enter the saved-game's filename and extension: " << '\n';
		std::cin >> user_input;
		c.SetupBoard(user_input);
		c.debugPrint(std::cout); //Comment to use displayBoard
		//c.displayBoard(); uncomment to use displayBoard
	}
	else {
		c.SetupBoard("newgame.txt");
		c.debugPrint(std::cout); //Comment to use displayBoard
		//c.displayBoard(); uncomment to use displayBoard
	}
	while (1) {
		if (c.getTurn() == 1) {
			std::cout << "Red Player, please enter a move" << '\n' << "Enter Q to quit the game" << '\n' << "Enter S to save the game" << '\n';
		}
		else if (c.getTurn() == 0) {
			std::cout << "Black Player, please enter a move" << '\n' << "Enter Q to quit the game" << '\n' << "Enter S to save the game" << '\n';
		}
		std::cin >> mov;
		if (mov == "Q") {
			exit(0);
		}
		if (mov == "S") {
			std::string fileName;
			std::cout << "Please enter a filename to save the game" << '\n';
			std::cin >> fileName;
			c.SaveGame(fileName);
			exit(0);
		}
		std::cin >> from;
		std::cin >> to;
		if (c.MakeMove(mov, from, to) == 1) {
			c.setTurn();
			c.debugPrint(std::cout) << '\n'; //Comment to use displayBoard
			//c.displayBoard(); uncomment to use displayBoard
			std::cout << "Player's turn is completed" << '\n';
		}
		else {
			c.debugPrint(std::cout) << '\n'; //Comment to use displayBoard
			//c.displayBoard(); uncomment to use displayBoard
			std::cout << "Player's turn is incomplete, no move" << '\n';
		}
		c.makeKing();
	}
}