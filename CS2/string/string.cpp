// CS2_string_Milestone2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "string.hpp"
#include <cassert>
#include <vector>

//Private member functions//////////////////////////
//String(10) - size of 10.
String::String(int size) {
	if (size < 0) {
		stringSize = 1;
		str = new char[stringSize];
		str[0] = 0;
	}
	else {
		stringSize = size + 1;
		str = new char[stringSize];
		str[0] = 0;
	}
}
//String(10, "abc") - Size 10 with "abc"
String::String(int size, const char c[]) : String(size) {
	if (c[0] == '\0') {
		str[0] = '\0';
	}
	else {
		int i = 0;
		while (c[i] != '\0') {
			str[i] = c[i];
			i++;
		} str[i] = '\0';
	}
}
//Resets capacity to be N
void String::resetCapacity(int newcap) {
	stringSize = newcap + 1;
	/*
	char *tmp = str;
	str = new char[stringSize];
	int i = 0;
	while (tmp[i] != '\0' && i < stringSize) {
		str[i] = tmp[i];
		i++;
	} str[i] = '\0';
	delete tmp;
	*/
	char *tmp = new char[stringSize];
	int i = 0;
	while(str[i] != '\0' && i < stringSize){
		tmp[i] = str[i];
		++i;
	}
	tmp[i] = '\0';
	delete[] str;
	str = tmp;
}
////////////////////////////////////////////////////
//Public member functions
//Empty string
String::String() : String(0) {
	str[0] = '\0';
}
//String('x')
String::String(char c) : String(1) {
	str[0] = c;
	str[1] = '\0';
}
//String("abcd")
String::String(const char c[]) {
	if (c[0] == '\0') {
		str = new char[1];
		str[0] = '\0';
		stringSize = 0;
	}
	else {
		//Find c's size
		int size = 0;
		while (c[size] != '\0') {
			size++;
		} stringSize = size + 1;
		str = new char[stringSize]; //Allocate appropriate mem									  
		//Store c into newly created memory
		for (int i = 0; i < size; i++) {
			str[i] = c[i];
		} str[size] = '\0';
	}
}
//Copy Constructor
String::String(const String& old_str) {
	//std::cout << "Copy Constructor" << '\n';
	stringSize = old_str.stringSize;
	//std::cout << "Copy constructor allocates space for, this many chars: " << stringSize << '\n';
	str = new char[stringSize];
	//std::cout << stringSize;
	int i = 0;
	while (old_str.str[i] != '\0') {
		str[i] = old_str.str[i];
		i++;
	} 
	//Valgrind says a bad write happens here
	//std::cout << "Copy Constructor write null terminator to space: " << i << '\n';
	str[i] = '\0';
}
//Destructor
String::~String() {
	//std::cout << "Destructor" << '\n';
	stringSize = 0;
	delete[] str;
}
//Constant time swap
void String::swap(String& rhs) {
	//Error might be here
	char*tmp = str; //current to temp storage (There may be a problem with this because it doesn't work as after this->str replace)
	int tmpSize = stringSize;
	str = rhs.str; //current equals other
	stringSize = rhs.stringSize;
	rhs.str = tmp; //other equals current
	rhs.stringSize = tmpSize;
}
//Assignment operator
String& String::operator= (String s) {
	swap(s);
	return *this;
}
//Accessor/Modifier
char& String::operator[](int i) {
	return str[i];
}
//Accessor
char String::operator[](int i) const {
	return str[i];
}
//Max chars that can be stored (not including null terminator)
int String::capacity() const {
	if (stringSize == 0) {
		return 0;
	}
	return (stringSize) - 1;
}
//Actual number of chars in string
int String::length() const {
	int counter = 0;
	while (str[counter] != '\0') {
		counter++;
	} return counter;
}
//Concatenation
String String::operator+(const String& s) const {
	//Added +1 for null-terminator
	int size = s.length() + length();
	String a(size);
	for (int i = 0; i < length(); i++) {
		a.str[i] = str[i];
	}
	for (int i = length(); i < size + 1; i++) {
		a.str[i] = s.str[i - length()];
		if (i == size) {
			//a.str[1+1] = '\0', removed +1 to fix valgrind issue
			a.str[i] = '\0';
		}
	}
	return a;
}
//a=a+b -> a+=b
String& String::operator+= (const String& s) {
	int size = s.length() + length();
	int thisLength = length();
	resetCapacity(size);
	for (int i = 0; i < size + 1; i++) {
		str[thisLength + i] = s.str[i];
		if (i == size) {
			str[(thisLength + i) + 1] = '\0';
		}
	}
	return *this;
}
bool String::operator== (const String& s) const {
	if (str[0] == '\0' && s.str[0] == '\0') {
		return 1;
	}
	else if (length() != s.length()) {
		return 0;
	}
	else {
		for (int i = 0; i <= length(); i++) {
			if (str[i] != s.str[i]) {
				return 0;
			}
		}
		return 1;
	}
}
bool String::operator<(const String& s) const {
	int i = 0;
	if (length() < s.length()) {
		while (str[i] != '\0') {
			if (str[i] < s.str[i]) {
				return 1;
			}
			else if (str[i] > s.str[i]) {
				return 0;
			}
			else {
				i++;
			}
		}  return 1;
	}
	else if (length() == s.length()) {
		while (str[i] != '\0') {
			if (str[i] < s.str[i]) {
				return 1;
			}
			else {
				i++;
			}
		} return 0;
	}
	else if (length() > s.length()) {
		while (s.str[i] != '\0') {
			if (str[i] < s[i]) {
				return 1;
			}
			else {
				i++;
			}
		} return 0;
	}
	std::cout << "Less Than Comparison was bad:  returning 1" << '\n';
	return 1;
}
//The sub-string from staring position to ending position
String String::substr(int start, int end) const {
	if (str[0] == '\0') {
		String aSubStrEmp("");
		return aSubStrEmp;
	}
	if (end >= start) {
		String aSubStr(end - start + 1);
		for (int i = start; i <= end; i++) {
			aSubStr.str[i - start] = str[i];
		} aSubStr.str[(end - start) + 1] = '\0';
		return aSubStr;
	}
	else if (start > end) {
		String aSubStr("");
		return aSubStr;
	}
	std::cout << "SubStr was bad:  returning badSubStr" << '\n';
	return "badSubStr";
}
//Find location of charater starting at a position
int String::findch(int i, char c) const {
	if (i >= stringSize || i < 0) {
		return -1;
	}
	else {
		while (i < stringSize) {
			if (str[i] == c) {
				return i;
			}
			else {
				i++;
			}
		}
	}
	return -1;
}
//Find location of str starting at a position
int String::findstr(int pos, const String& s) const {
	if (str[0] == '\0') {
	}
	if (pos >= stringSize || pos < 0) {
	}
	int tmp = 0;
	while (str[pos] != '\0') {
		if (str[pos] == s[0]) {
			tmp = pos;
			String result;
			result = substr(pos, pos + (s.length() - 1));
			if (result == s) {
				return pos;
			}
			else {
				pos++;
			}
		}
		else {
			pos++;
		}
	} return -1;
}
int String::stoi() {
	int z = 0;
	int i = 0;
	if (str[z] == '-')
	{
		return 0;
	}
	while (str[z] != '\0') {
		if (str[z] >= '0' && str[z] <= '9') {
			i = i * 10 + (str[z] - '0');
			z++;
		}
		else {
			std::cout << "Bad Input";
			return 1;
		}
	}
	return i;
}
std::vector<String> String::split(char ch) const {
	std::vector<String> result;
	int start = 0;
	int splitAt = findch(start, ch);
	int i = 0;
	while(splitAt != -1){
		//std::cout << i << substr(start, splitAt-1) << '\n';
		result.push_back(substr(start, splitAt-1));
		start = splitAt + 1;
		splitAt = findch(start, ch);
		i++;
	}
	//std::cout << "9 " << substr(start, length() - 1) << '\n';
	result.push_back(substr(start, length()-1));
	return result;
}
std::istream& operator>>(std::istream& input, String& rhs) {
	input >> rhs.str;
	return input;
}
String getline(std::istream& in)
{
	String line;
	char ch = '\0';

	for (int i = (in.get(ch), 0); (ch != '\n') && (!in.fail()); ++i, in.get(ch)){
		line = line + ch;
	}
	return line;
}
std::ostream& operator<<(std::ostream& out, const String& str) {
	int i = 0;
	while (str.str[i] != '\0') {
		out << str.str[i];
		i++;
	} out << '\0';
	return out;
}
String  operator+  (const char rhs[], const String& lhs) {
	String a(rhs);
	String result = a + lhs;
	return result;
}
String  operator+  (char ch, const String& str) {
	String a(ch);
	String result = a + str;
	return result;
}
bool operator== (const char c[], const String& str) {
	int i = 0;
	if (c[0] == '\0' && str[0] == '\0') {
		return 1;
	}
	while (c[i] != '\0') {
		i++;
	} if (i != str.length()) {
		return 0;
	}
	else {
		for (int z = 0; z < str.length(); z++) {
			if (str[z] != c[z]) {
				return 0;
			}
		}
		return 1;
	}
}
bool operator== (char ch, const String& str) {
	if (ch == '\0' && str[0] == '\0') {
		return 1;
	}
	else {
		return String(ch) == str;
	}
}
bool operator<  (const char rhs[], const String& lhs) {
	int sizeOfRHS = 0;
	while (rhs[sizeOfRHS] != '\0') {
		sizeOfRHS++;
	}
	int i = 0;
	if (sizeOfRHS < lhs.length()) {
		while (rhs[i] != '\0') {
			if (rhs[i] < lhs[i]) {
				return 1;
			}
			else {
				i++;
			}
		} return 1;
	}
	else if (sizeOfRHS == lhs.length()) {
		while (rhs[i] != '\0') {
			if (rhs[i] < lhs[i]) {
				return 1;
			}
			else {
				i++;
			}
		} return 0;
	}
	else if (sizeOfRHS > lhs.length()) {
		while (lhs[i] != '\0') {
			if (rhs[i] < lhs[i]) {
				return 1;
			}
			else {
				i++;
			}
		} return 0;
	}
	std::cout << "Less Than Comparison was bad:  returning 1" << '\n';
	return 1;
}
bool operator<  (char ch, const String& str) {
	if (ch < str[0]) {
		return 1;
	}
	else {
		return 0;
	}
}
bool operator<= (const String& rhs, const String& lhs) {
	int i = 0;
	if (rhs.length() == lhs.length()) {
		while (rhs[i] != '\0') {
			if (rhs[i] == lhs[i]) {
				i++;
			}
			else if (rhs[i] < lhs[i]) {
				return 1;
			}
			else {
				return 0;
			}
		} if (rhs[i] == '\0') {
			return 1;
		}
		else {
			return 0;
		}
	}
	if (rhs.length() < lhs.length()) {
		if (rhs[0] == '\0') {
			return 1;
		}
		while (rhs[i] != '\0') {
			if (rhs[i] == lhs[i]) {
				i++;
			}
			if (rhs[i] < lhs[i]) {
				return 1;
			}
			if (rhs[i] > lhs[i]) {
				return 0;
			}
			else {
				i++;
			}
		}
	}
	if (rhs.length() > lhs.length()) {
		if (lhs[0] == '\0') {
			return 0;
		}
		while (lhs[i] != '\0') {
			if (rhs[i] == lhs[i]) {
				i++;
			}
			if (rhs[i] < lhs[i]) {
				return 1;
			}
			if (rhs[i] > lhs[i]) {
				return 0;
			}
			else {
				i++;
			}
		}
	}
	std::cout << "LessThen-EqualToo was bad:  returning 1" << '\n';
	return 1;
}
bool operator!= (const String& rhs, const String& lhs) {
	if (rhs.length() != lhs.length()) {
		return 1;
	}
	else {
		int i = 0;
		while (rhs[i] != '\0') {
			if (rhs[i] != lhs[i]) {
				return 1;
			}
			else {
				i++;
			}
		}
		return 0;
	}
}
bool operator>= (const String& rhs, const String& lhs) {
	if (rhs.length() < lhs.length()) {
		return 0;
	}
	else {
		return 1;
	}
}
bool operator>  (const String& rhs, const String& lhs) {
	if (rhs.length() > lhs.length()) {
		return 1;
	}
	else {
		return 0;
	}
}
