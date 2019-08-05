// CS2_Lab03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include "bigint.hpp"
#include <fstream>

int main()
{

	std::ifstream input_file("data1-2.txt");

	if (!input_file.is_open()) { //Checks if input file opened successfully.
		std::cout << "Input file not opened";
	}
	else {
		while (!input_file.eof()) {
			bigint b_i_one = 0;
			bigint b_i_two = 0;
			input_file >> b_i_one;
			b_i_one.debugPrint(std::cout);
			std::cout << '\n' << '\n';
			//input_file.get();
			input_file >> b_i_two;
			b_i_two.debugPrint(std::cout);
			std::cout << '\n' << '\n' << "Result:" << '\n';
			bigint result = b_i_one * b_i_two;
			result.debugPrint(std::cout);
			std::cout << '\n' << "-------------------------------------------------------------" << '\n';
		}
		input_file.close();

	}
}