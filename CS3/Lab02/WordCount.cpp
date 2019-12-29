// CS3_Lab02_WordCount.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

using std::cout; using std::endl;

class WordOccurrence {
public:
	WordOccurrence(const std::string& word = "", int num = 0) {
		word_ = word;
		num_ = num;
	}
	// returns true if word matches stored
	bool matchWord(const std::string & aWord) {
		return (word_ == aWord);
	}
	// increments number of occurrences
	void increment() {
		++num_;
	}
	std::string getWord() const {
		return word_;
	}
	int getNum() const {
		return num_;
	}
private:
	std::string word_;
	int num_;
};

class WordList {
public:
	// Default Constructor
	WordList() {
		wordArray_ = new WordOccurrence[1];
		size_ = 0;
	}

	// copy constructor
	WordList(const WordList& other) {
		size_ = other.size_;
		wordArray_ = size_ > 0 ? new WordOccurrence[size_] : nullptr;
		std::copy(other.wordArray_, other.wordArray_ + size_, wordArray_);
	}

	// destructor
	~WordList() { delete[] wordArray_; }

	// "standard" assignment overloading
	WordList& operator=(const WordList& other) {
		if (this != &other) { // protection against self assingment
			delete[] wordArray_;
			size_ = other.size_;
			wordArray_ = size_ > 0 ? new WordOccurrence[size_] : nullptr;
			std::copy(other.wordArray_, other.wordArray_ + size_, wordArray_);
		}
		return *this;
	}

	// implement comparison as friend
	friend bool equal(const WordList& lhs, const WordList& rhs) {
		if (rhs.size_ != lhs.size_) {
			return false;
		}
		else {
			for (int i = 0; i < rhs.size_; i++) {
				if (rhs.wordArray_[i].getWord() != lhs.wordArray_[i].getWord()) {
					return false;
				}
			}
		}
		return true;
	}

	void addWord(const std::string &aWord) {
		bool matched = false;
		if (aWord.size() > 0) {
			for (int i = 0; i < size_; i++) {
				if (wordArray_[i].matchWord(aWord)) {
					wordArray_[i].increment();
					matched = true;
				}
			}
			if (matched == false) {
				if (size_ == 0) {
					wordArray_ = new WordOccurrence[1];
					wordArray_[0] = WordOccurrence(aWord, 1);
					size_ = 1;
				}
				else {
					// Create new space of size_ + 1
					WordOccurrence * tmp = new WordOccurrence[size_ + 1];
					// Copy elements to new empty space
					for (int i = 0; i < size_; i++) {
						tmp[i] = wordArray_[i];
					}
					// Place word into final element space
					tmp[size_] = WordOccurrence(aWord, 1);
					delete[] wordArray_;
					// Assign to wordArray
					wordArray_ = tmp;
					++size_;
				}
			}
		}
	}

	// Customer comparator
	static bool sortByNum(WordOccurrence lhs, WordOccurrence rhs)
	{
		return lhs.getNum() < rhs.getNum();
	}

	// Sorts the word list in asc-order by num_
	void sortWordList() {
		std::sort(wordArray_, wordArray_ + size_, sortByNum);
	}

	// Prints all the word occurences in word list
	void print() {
		sortWordList();
		//Add sort here, then print
		for (int i = 0; i < size_; i++) {
			std::cout << wordArray_[i].getWord() << " " << wordArray_[i].getNum() << '\n';
		}
	}
private:
	WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
								// may or may not be sorted
	int size_;
};

void testfunc(WordList); // function to test pass-by-value for WordList class

std::string& cleanStrOfPunct(std::string&); // Clean punct from string

int main(int argc, char** argv) {

	std::string args[2] = { "Nothing", "fileIn.txt" };
	std::ifstream fileIn;
	//fileIn.open(args[1]);
	if (argc > 2) {
		std::cout << "Too many arguments";
		return 0;
	}
	fileIn.open(argv[1]);

	WordList aList;

	while (!fileIn.eof()) {
		std::string str, word;
		std::getline(fileIn, str);
		std::stringstream ss(str);
		while (ss >> word) {
			aList.addWord(cleanStrOfPunct(word));
		}
	}
	aList.print();
	return 1;

	/*
	WordList w;

	// testing regular member functions
	w.addWord("one");
	w.addWord("one"); // adding duplicate
	w.addWord("two");
	w.addWord("three");

	cout << "word list is:\n";
	w.print();


	WoeqrdList w2, w3;

	w3 = w2 = w; // testing stacked overloaded assignment
	w3 = w3; // testing protection against self-assingment

	if (equal(w2, w3))
		cout << "w2 is equal to w3" << endl;
	else
		cout << "w2 is not equal to w3" << endl;

	testfunc(w); // testing copy constructor
	w.print(); // if destructor is implemented correctly
				 // this should print properly after testfunc completes
	*/
}


// tests pass-by-value for object of class varArray
void testfunc(WordList myList) { // copy constructor is invoked on "myList"
	cout << "word list in testfunc: " << endl;
	myList.print();
} // destructor is invoked when "myList" goes out of scope

std::string& cleanStrOfPunct(std::string& str) {
	for (int i = 0, len = str.size(); i < len; i++)
	{
		// check whether parsing character is punctuation or not 
		if (ispunct(str[i]))
		{
			str.erase(i--, 1);
			len = str.size();
		}
	}
	return str;
}
