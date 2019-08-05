//fileTransform2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Name: Matthew Miller
//Kent Id: mmill199@kent.edu
//Date: 1/20/2019

#include <fstream>
#include <iostream>

using namespace std;

struct input_record {
	char Name[21];
	char Id[10];
	char Crn[6];
	char Section[4];
	char Score[4];
	char Answer[256];
};

void printRecord(input_record record, ofstream& csvOutput);
input_record processLine(char* str);

int main()
{
	char str[256];

	//Error check, input file open
	ifstream txtInputFile("testfile.txt");
	if (!txtInputFile.is_open()) {
		cout << "Input file not opened";
	}
	//Error check, output file open
	ofstream csvOutputFile("filetest2.csv");
	if (!csvOutputFile.is_open()) {
		cout << "file not opened";
	}
	//Main loop: file read, process line, and print record
	while (txtInputFile.getline(str, 256, '\n')) {
		input_record record = processLine(str);
		printRecord(record, csvOutputFile);
	}

	cout << "press any key to exit";
	cin.get();

	txtInputFile.close();
	csvOutputFile.close();
}

void printRecord(input_record record, ofstream& csvOutput) {
	//Output to console
	cout << record.Name << ',' << record.Id << ',' << record.Crn << ',' << record.Section << ',' << record.Score << ',';
	for (int i = 0; record.Answer[i] != '\0'; i++) {
		cout << record.Answer[i] << ',';
	} cout << '\n';

	//Output to file
	csvOutput << record.Name << ',' << record.Id << ',' << record.Crn << ',' << record.Section << ',' << record.Score << ',';
	for (int i = 0; record.Answer[i] != '\0'; i++) {
		csvOutput << record.Answer[i] << ',';
	} csvOutput << '\n';
}

input_record processLine(char* str) {
	
	//Initialize record struct
	input_record record;

	//read name field to string variable
	for (int i = 0; i <= 21; i++) {
		if ((str[i] == ' ') && (str[i + 1] == ' ')) {
			record.Name[i] = '\0';
			break;
		}
		record.Name[i] = str[i];
	}
	//read id field positions
	for (int i = 31; i < 40; i++) {
		if (str[31] == ' ') {
			record.Id[0] = ' ';
			record.Id[1] = '\0';
			break;
		}
		record.Id[i - 31] = str[i];
		record.Id[9] = '\0';
	}
	//read CRN field positions
	for (int i = 41; i < 46; i++) {
		if (str[41] == ' ') {
			record.Crn[0] = ' ';
			record.Crn[1] = '\0';
			break;
		}
		record.Crn[i - 41] = str[i];
		record.Crn[5] = '\0';
	}
	//read section positions
	for (int i = 48; i < 51; i++) {
		if (str[48] == ' ') {
			record.Section[0] = ' ';
			record.Section[1] = '\0';
			break;
		}
		record.Section[i - 48] = str[i];
		record.Section[3] = '\0';
	}
	//read score field positions
	for (int i = 51; i < 54; i++) {
		if (str[51] == ' ') {
			if (str[52] == ' ') {
				record.Score[0] = str[i + 2];
				record.Score[1] = '\0';
				break;
			}
			else {
				record.Score[0] = str[i + 1];
				record.Score[1] = str[i + 2];
				record.Score[2] = '\0';
				break;
			}
		}
		record.Score[i - 51] = str[i];
		record.Score[3] = '\0';
	}
	//read remaining answer positions
	for (int i = 54; i < 106; i++) {
		record.Answer[i - 54] = str[i];
		record.Answer[107] = '\0';
	}
	return record;
}
