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

		std::pair<std::string::iterator, std::string::iterator> result;

		/* ------------------------------ Loop through each character of lines ---------------------------- */
		// Case where file1 line is longer than file2 line
		if (aLine[0].length() >= aLine[1].length()) {
			result = mismatch(aLine[0].begin(), aLine[0].end(), aLine[1].begin(), [](char c, char d) { return c == d; });
			//Case where none matched
			if (result == std::make_pair(aLine[0].begin(), aLine[1].begin())) {
				whiteSpaceCount = fileNameLength + 2 + std::to_string(lineCount).length() + 2;
				printOutput(args, lineCount, whiteSpaceCount, aLine);
				return 1;
			}
			//Case where lines are equal
			else if (result.first == aLine[0].end() && result.second == aLine[1].end()) {
				//std::cout << "Equal lines" << std::endl;
			}
			//Case where there is a mismatch on a line
			else {
				whiteSpaceCount = fileNameLength + 2 + std::to_string(lineCount).length() + 2 + (result.first - aLine[0].begin());
				printOutput(args, lineCount, whiteSpaceCount, aLine);
				return 1;
			}
		}
		// Case where file2 line is longer than file1 line
		else {
			result = mismatch(aLine[1].begin(), aLine[1].end(), aLine[0].begin(), [](char c, char d) { return c == d; });
			// Case where none match, point to first space
			if (result == std::make_pair(aLine[1].begin(), aLine[0].begin())) {
				whiteSpaceCount = fileNameLength + 2 + std::to_string(lineCount).length() + 2;
				printOutput(args, lineCount, whiteSpaceCount, aLine);
				return 1;
			}
			//Case of equal lines, all chars match
			else if (result.first == aLine[1].end() && result.second == aLine[0].end()) {
				
			}
			//Case where there is a mismatch in line 2
			else {
				//Use iterator arithmetic to calculate white space at end
				whiteSpaceCount = fileNameLength + 2 + std::to_string(lineCount).length() + 2 + (result.first - aLine[1].begin());
				printOutput(args, lineCount, whiteSpaceCount, aLine);
				return 1;
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
	std::cout << spaceString << "^" << std::endl; // Print black space and carat to mark start of line-diff
}