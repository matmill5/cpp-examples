#include <iostream>
#include <fstream>
#include "utilities.hpp"
#include "stack.hpp"
#include "string.hpp"

int main(int argc, char const* argv[])
{
	if (argc < 2) {
		std::cerr << "No input file found" << '\n';
	}

	std::ifstream infixFile(argv[1]);

	if (!infixFile) {
		std::cerr << "Infix file didnt open" << '\n';
	}

	std::ofstream postfixFile(argv[2]);

	if (!postfixFile) {
		std::cerr << "Output file didnt open" << '\n';
		infixToPostFix(infixFile, postfixFile);
	}

	infixToPostFix(infixFile, postfixFile);

	infixFile.close();
	postfixFile.close();

	return 0;
}