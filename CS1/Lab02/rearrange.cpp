// CS1_Lab02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string> 

using namespace std;

struct input_record {
	string FName;
	string LName;
	string Gender;
	int Age;
};

input_record* processFileEntryIntoStructArray(int i, input_record* ALL_Records, ifstream& txtInputFile1, string line);
void printFileStatsToConsole(int maleCountFile1, int maleCountFile2, int femaleCountFile1, int femaleCountFile2, int totalMaleAge, int totalFemaleAge);
void printStructArrayToFile(input_record* ALL_Records, int arrayLength, ofstream& txtFemaleOutputFile, ofstream& txtMaleOutputFile);

int main()
{
	//Variable declaration
	char str[256];
	string line;
	int lineCountFile1 = 0;
	int lineCountFile2 = 0;
	int arrayLength = 0;
	int maleCountFile1 = 0;
	int maleCountFile2 = 0;
	int femaleCountFile1 = 0;
	int femaleCountFile2 = 0;
	int totalFemaleAge = 0;
	int totalMaleAge = 0;

	//Open file1
	ifstream txtInputFile1("datafile1.txt");
	if (!txtInputFile1.is_open()) {
		cout << "file1 not opened";
	}
	//Open file2
	ifstream txtInputFile2("datafile2.txt");
	if (!txtInputFile2.is_open()) {
		cout << "file2 not opened";
	}

	//Main Loop: file read, process line
	//Read file 1's line count from line one
	txtInputFile1.getline(str, 256, '\n');
	lineCountFile1 = (str[0] - '0');
	arrayLength = arrayLength + lineCountFile1;

	//Read file 2's line count from line two
	txtInputFile2.getline(str, 256, '\n');
	lineCountFile2 = (str[0] - '0');
	arrayLength = arrayLength + lineCountFile2;

	//Create a new dynamic memory array of length, total file entries
	input_record * ALL_Records = NULL;
	ALL_Records = new input_record[arrayLength];

	//Process file 1's information into dynamic memory array
	int i = 0;
	while (i < lineCountFile1) {
		
		processFileEntryIntoStructArray(i, ALL_Records, txtInputFile1, line);

		if (ALL_Records[i].Gender == "M") {
			totalMaleAge = totalMaleAge + ALL_Records[i].Age;
			maleCountFile1++;
		}
		if (ALL_Records[i].Gender == "F") {
			totalFemaleAge = totalFemaleAge + ALL_Records[i].Age;
			femaleCountFile1++;
		}
		i++;
	}
	//Process file 2's information into dynamic memory array
	while (i < (lineCountFile1 + lineCountFile2)) {

		processFileEntryIntoStructArray(i, ALL_Records, txtInputFile2, line);

		if (ALL_Records[i].Gender == "M") {
			totalMaleAge = totalMaleAge + ALL_Records[i].Age;
			maleCountFile2++;
		}
		if (ALL_Records[i].Gender == "F") {
			totalFemaleAge = totalFemaleAge + ALL_Records[i].Age;
			femaleCountFile2++;
		}
		i++;
	}

	//Close files after all information has been read.
	txtInputFile1.close();
	txtInputFile2.close();

	//Open output file stream
	ofstream txtFemaleOutputFile("datafile1.txt");
	ofstream txtMaleOutputFile("datafile2.txt");
	
	//Place female and male counts in respective files
	txtFemaleOutputFile << (femaleCountFile1 + femaleCountFile2) << " " << "female" << '\n';
	txtMaleOutputFile << (maleCountFile1 + maleCountFile2) << " " << "male" << '\n';

	//Print required material to file and console
	printStructArrayToFile(ALL_Records, arrayLength, txtFemaleOutputFile, txtMaleOutputFile);
	printFileStatsToConsole(maleCountFile1, maleCountFile2, femaleCountFile1, femaleCountFile2, totalMaleAge, totalFemaleAge);
	
	//Close files
	txtFemaleOutputFile.close();
	txtMaleOutputFile.close();
}

input_record* processFileEntryIntoStructArray(int i, input_record* ALL_Records, ifstream& txtInputFile, string line) {
	
	getline(txtInputFile, line, ' ');
	ALL_Records[i].FName = line;
	getline(txtInputFile, line, ' ');
	ALL_Records[i].LName = line;
	getline(txtInputFile, line, ' ');
	ALL_Records[i].Gender = line;
	getline(txtInputFile, line, '\n');
	ALL_Records[i].Age = stoi(line);

	return ALL_Records;
}

void printFileStatsToConsole(int maleCountFile1, int maleCountFile2, int femaleCountFile1, int femaleCountFile2, int totalMaleAge, int totalFemaleAge) {
	double avgMaleAge = 0;
	double avgFemaleAge = 0;

	//Send prompt to console
	cout << "datafile1.txt contained " << femaleCountFile1 << " female names and " << maleCountFile1 << " male names" << '\n';
	cout << "datafile2.txt contained " << femaleCountFile2 << " female names and " << maleCountFile2 << " male names" << '\n' << '\n';

	//Calculate average age of male and females
	avgMaleAge = ((double)(totalMaleAge) / (double)(maleCountFile1 + maleCountFile2));
	avgFemaleAge = ((double)(totalFemaleAge) / (double)(femaleCountFile1 + femaleCountFile2));

	//Send prompt to console
	cout << "The average age of the " << (femaleCountFile1 + femaleCountFile2) << " females is " << avgFemaleAge << '\n';
	cout << "The average age of the " << (maleCountFile1 + maleCountFile2) << " males is " << avgMaleAge << '\n';
}

void printStructArrayToFile(input_record* ALL_Records, int arrayLength, ofstream& txtFemaleOutputFile, ofstream& txtMaleOutputFile) {
	//Iterate through dynamic memory array, printing struct's information to output files
	for (int i = 0; i < arrayLength; i++) {
		if (ALL_Records[i].Gender == "M") {
			txtMaleOutputFile << ALL_Records[i].FName << " ";
			txtMaleOutputFile << ALL_Records[i].LName << " ";
			txtMaleOutputFile << ALL_Records[i].Age << '\n';
		}
		if (ALL_Records[i].Gender == "F") {
			txtFemaleOutputFile << ALL_Records[i].FName << " ";
			txtFemaleOutputFile << ALL_Records[i].LName << " ";
			txtFemaleOutputFile << ALL_Records[i].Age << '\n';
		}
	}
}