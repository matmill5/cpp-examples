// vector and list algorithms with objects in containers
// Matthew E. Miller
// 9/20/2019

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student {
public:
	Student(string firstName, string lastName) :
		firstName_(firstName), lastName_(lastName) {}

	// move constructor, not really needed, generated automatically
	Student(Student && org) :
		firstName_(move(org.firstName_)),
		lastName_(move(org.lastName_))
	{}

	// force generation of default copy constructor
	Student(const Student & org) = default;

	void setCourses(std::string aStr) {
		courses_ = courses_ + aStr;
	}

	string print() const { return firstName_ + ' ' + lastName_ + ' ' + courses_; }

	// needed for unique() and for remove()
	friend bool operator== (Student left, Student right) {
		return left.lastName_ == right.lastName_ &&
			left.firstName_ == right.firstName_;
	}

	// needed for sort()
	friend bool operator< (Student left, Student right) {
		return left.lastName_ < right.lastName_ ||
			(left.lastName_ == right.lastName_ &&
				left.firstName_ < right.firstName_);
	}
private:
	string firstName_;
	string lastName_;
	string courses_;
};

// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);
// printing a list out
void printRoster(const list<Student>& roster);

int main(int argc, char* argv[]) {

	if (argc <= 1) {
		cout << "usage: " << argv[0]
			<< " list of courses, dropouts last"
			<< endl; exit(1);
	}

	// vector of courses of students
	list<Student> courseStudents;

	for (int i = 1; i < argc; ++i) {
		readRoster(courseStudents, argv[i]);
	}

	printRoster(courseStudents);
}


void readRoster(list<Student>& roster, string fileName) {
	ifstream course(fileName);
	string first, last;

	while (course >> first >> last) {
		bool found = false;
		for (auto& aLst : roster) {
			if (aLst == Student(first, last)) {
				found = true;
				aLst.setCourses(" " + fileName.substr(0, fileName.find(".txt")));
				break;
				//then exist
				//add course name to aLst and remove .txt
			}
		}
		if (!found) {
			Student aStudent(first, last);
			aStudent.setCourses(" " + fileName.substr(0, fileName.find(".txt")));
			roster.push_back(aStudent);
		}
	}
	course.close();
}

// printing a list out
void printRoster(const list<Student>& roster) {
	std::cout << "All Students" << endl;
	std::cout << "last name, first name : courses enrolled" << endl;
	for (const auto& student : roster)
		cout << student.print() << endl;
}
