#include <fstream>
#include "stack.hpp"
#include "string.hpp"
#include "utilities.hpp"

int main(int argc, char const* argv[])
{
	if (argc < 2) {
		std::cerr << "No input file found" << '\n';
	}

	std::ifstream postfixFile(argv[1]);

	if (!postfixFile) {
		std::cerr << "Infix file didnt open" << '\n';
	}

	std::ofstream asmFile(argv[2]);

	if (!asmFile) {
		std::cerr << "Output file didnt open" << '\n';
		//infixToPostFix(infixFile, postfixFile);
	}

	postFixToAsm(postfixFile, asmFile);

	postfixFile.close();
	asmFile.close();

	return 0;
}