//fileIO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Matthew Miller
//Kent ID: mmill199@kent.edu
//Date: 1/20/2019


#include <fstream>
#include <iostream>

using namespace std;

int main() {
	char str[256]; //Defines a new character array for storing characters from input file.
	int counter = 0;
	string userInput;

	cout << "Enter an input file's name or press 1 to continue using testFile.txt: ";
	userInput = cin.get();

	if (userInput == "1") {

		ifstream input_file("testfile.txt"); //Opens input file stream for file that will be read from.

		if (!input_file.is_open()) { //Checks if input file opened successfully.
			cout << "Input file not opened";
		}
		else {
			while (input_file.getline(str, 256, '\n')) { //Loops through each line of the file, writing the file's information to the console, then to the output file.
				cout << str << "\n";
				counter++;
			}
			input_file.close();
			cout << "Processed Lines: " << counter << '\n';
			cout << "press any key to exit";
			cin.get();
		}
	}

	else {
		ifstream input_file(userInput.c_str()); //Opens input file stream for file that will be read from.

		if (!input_file.is_open()) { //Checks if input file opened successfully.
			cout << "Input file not opened";
		}
		else {
			while (input_file.getline(str, 256, '\n')) { //Loops through each line of the file, writing the file's information to the console, then to the output file.
				cout << str << "\n";
				counter++;
			}
			input_file.close();
			cout << "Processed Lines: " << counter << '\n';
			cout << "press any key to exit";
			cin.get();
		}
	}
}
