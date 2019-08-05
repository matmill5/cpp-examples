#include <iostream>
#include <fstream>
#include "bigint.hpp"


int main()
{
	bigint b_i_one;
	bigint b_i_two;
	bigint result;

	std::ifstream input_file("data1-1.txt");

	if (!input_file.is_open()) { //Checks if input file opened successfully.
		std::cout << "Input file not opened";
	}
	else {
		while (!input_file.eof()) {
			b_i_one = 0;
			b_i_two = 0;
			input_file >> b_i_one;
			b_i_one.debugPrint(std::cout);
			std::cout << '\n' << '\n';
			//input_file.get();
			input_file >> b_i_two;
			b_i_two.debugPrint(std::cout);
			std::cout << '\n' << '\n' << "Result:" << '\n';
			result = b_i_one + b_i_two;
			result.debugPrint(std::cout);
			std::cout << '\n' << "-------------------------------------------------------------" << '\n';
		}
		input_file.close();
		
	}
}