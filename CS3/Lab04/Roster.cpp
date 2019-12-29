// Roster
// Matthew E. Miller
// 9/20/2019

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <cctype>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(vector<list<string>>& roster, string fileName);

// printing a list out
void printRoster(const vector<list<string>>& roster);

int main(int argc, char* argv[]) {

	if (argc <= 1) {
		cout << "usage: " << argv[0]
			<< " list of courses, dropouts last"
			<< endl; exit(1);
	}

	// vector of courses of students
	vector <list<string>> courseStudents;

	for (int i = 1; i < argc; ++i) {
		readRoster(courseStudents, argv[i]);
	}

	printRoster(courseStudents);
}

// reading in a file of names into a list of strings
void readRoster(vector<list<string>>& roster, string fileName) {
	ifstream course(fileName);
	string first, last, name;
	while (course >> first >> last) {
		name = first + " " + last + ":";
		bool found = false;
		for (auto& aLst : roster) {
			if (aLst.front() == name) {
				found = true;
				aLst.back().append(" " + fileName.substr(0, fileName.find(".txt")));
				break;
				//then exist
				//add course name to aLst and remove .txt
			}
		}
		if (!found) {
			list<string> newStudent;
			newStudent.push_back(name);
			newStudent.push_back(" " + fileName.substr(0, fileName.find(".txt")));
			roster.push_back(newStudent);
		}
	}
	course.close();
}

// printing a list out
void printRoster(const vector<list<string>>& roster) {
	std::cout << "All Students" << endl;
	std::cout << "last name, first name : courses enrolled" << endl;
	for (const auto& str : roster) {
		for (const auto& studentElement : str)
			cout << studentElement;
		cout << endl;
	}
}