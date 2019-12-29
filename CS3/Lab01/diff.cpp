// CS3_Lab01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <iostream>
#include <fstream>
#include <string>

// Function prototypes
void printOutput(std::string[], int, int, std::string[]);

int main(int argc, char* argv[]) {
	std::string args[3] = { (std::string)argv[0], (std::string)argv[1], (std::string)argv[2] };

	/* --------------------------------  Verify command line argument count  --------------------------- */
	if (argc != 3) {
		std::cout << "Bad Input, please provide 3 arguments";
		return 0; //Bad Input
	}
	/* ----------------------------------  End Verification  -------------------------------------------- */

	/* --------------------------------  Variable declaration  ------------------------------------------ */
	int lineCount = 0; // Holds line count
	std::string file1Name = args[1]; // Holds the name of file1
	std::string file2Name = args[2]; // Holds the name of file2
	int fileNameLength = file1Name.length(); // Holds length of filenames, assumed to be equal per documentation
	int whiteSpaceCount; // Holds the number of whitepspaces to place before the '^'

	std::ifstream  file1, file2; // Initialize file streams
	file1.open(file1Name); // Open file 1
	file2.open(file2Name); // Open file 2

	std::string aLine[2]; // Initializes an array of two strings
	/* ---------------------------------------  END  --------------------------------------------------- */

	// Work on each line of the files, until the end of file is reached.
	// Assume the files have the same number of lines, so eof() is the same for file1 or file2 as we grab a line from each.
	while (!file1.eof()) {
		std::getline(file1, aLine[0], '\n'); // Get line of file1
		std::getline(file2, aLine[1], '\n'); // Get line of file2
		lineCount++; // Increment line count

		/* ------------------------------ Loop through each character of lines ---------------------------- */
		if (aLine[0].length() >= aLine[1].length()) {
			for (int i = 0; i < (int)aLine[0].length(); i++) {
				if (aLine[0][i] != aLine[1][i]) {
					whiteSpaceCount = fileNameLength + 2 + std::to_string(lineCount).length() + 2 + i;
					printOutput(args, lineCount, whiteSpaceCount, aLine);
					return 1;
				}
			}
		}
		else {
			for (int i = 0; i < (int)aLine[1].length(); i++) {
				if (aLine[1][i] != aLine[0][i]) {
					whiteSpaceCount = fileNameLength + 2 + std::to_string(lineCount).length() + 2 + i;
					printOutput(args, lineCount, whiteSpaceCount, aLine);
					return 1;
				}
			}
		}
		/* ------------------------------ End Looping through each char of lines ---------------------------- */
	}

}

// Handles the printing of the program's output.
void printOutput(std::string args[], int lineCount, int whiteSpaceCount, std::string aLine[]) {
	std::cout << args[1] << ": " << lineCount << ": " << aLine[0] << '\n'; // First Line
	std::cout << args[2] << ": " << lineCount << ": " << aLine[1] << '\n'; // Second Line
	std::string spaceString(whiteSpaceCount, ' '); // Initilize spaces
	std::cout << spaceString << "^"; // Print black space and carat to mark start of line-diff
}