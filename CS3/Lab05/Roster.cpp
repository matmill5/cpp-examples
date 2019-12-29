// CS3_Lab05_Roster_Map.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Matthew E. Miller

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(std::map<std::string, list<string>>& roster, string fileName);

// printing a list out
void printRoster(const std::map<std::string, list<string>>& roster);

int main(int argc, char* argv[]) {

	if (argc <= 1) {
		cout << "usage: " << argv[0]
			<< " list of courses, dropouts last"
			<< endl; exit(1);
	}

	// vector of courses of students
	std::map<std::string, list<string>> courseStudents;

	for (int i = 1; i < argc; ++i) {
		readRoster(courseStudents, argv[i]);
	}

	printRoster(courseStudents);
}

// reading in a file of names into a list of strings
void readRoster(std::map<std::string, list<string>>& roster, string fileName) {
	ifstream course(fileName);
	string first, last, name;
	//list<string> aLst;
	while (course >> first >> last) {
		name = first + " " + last;
		//aLst.push_back(fileName);
		roster.insert({ name, list<string>() });
		roster[name].push_back(fileName.substr(0,fileName.find('.')));
		//std::cout << roster[name].front();
		//roster.at(name).back().append(fileName);
	}
	course.close();
}

// printing a list out
void printRoster(const std::map<std::string, list<string>>& roster) {
	std::cout << "All Students" << endl;
	std::cout << "last name, first name : courses enrolled" << endl;
	for (auto element : roster) {
		std::cout << element.first << " ";
		for (auto file : element.second) {
			std::cout << file << " ";
		}
		std::cout << endl;
	}
}