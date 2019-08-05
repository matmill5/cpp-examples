// CS2_Lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

void fileioRead();
void fileioReadInt();

int main()
{
	fileioRead();
	fileioReadInt();
}

void fileioRead() {
	
	char str[256];

	std::ifstream input_file("fileio-text.txt");

	if (!input_file.is_open()) { //Checks if input file opened successfully.
		std::cout << "Input file not opened";
	}
	else {
		input_file.getline(str, 256, ' ');
		std::cout << str << "\n";
		input_file.close();
		//cout << "press any key to exit";
		//cin.get();
	}
}

void fileioReadInt() {
	char first_int[256];
	char second_int[256];
	int result;

	std::ifstream input_file("fileio-data-1.txt");

	if (!input_file.is_open()) { //Checks if input file opened successfully.
		std::cout << "Input file not opened";
	}
	else {
		if (!input_file.eof()) {
			input_file.getline(first_int, 256, ';');
			input_file.get();
			input_file.getline(second_int, 256, ';');
		}
		input_file.close();
		result = std::atoi(first_int);
		result = result + std::atoi(second_int);
		std::cout << first_int << " + " << second_int << " = " << result;
		//cout << "press any key to exit";
		//cin.get();
	}
}