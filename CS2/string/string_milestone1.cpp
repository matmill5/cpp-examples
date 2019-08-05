// CS2_string.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "string.hpp"
#include <cassert>

//Empty string
String::String() {
	str[0] = '\0';
}
//String('x')
String::String(char c) {
	str[0] = c;
	str[1] = '\0';
}
//String("abcd")
String::String(const char c[]) {
	int i = 0;
	while (c[i] != '\0') {
		str[i] = c[i];
		i++;
	} str[i] = '\0';
} 
//Accessor/Modifier
char& String::operator[](int i) {
	return this->str[i];
}
//Accessor
char String::operator[](int i) const {
	return this->str[i];
}
//Max chars that can be stored (not including null terminator)
int String::capacity() const {
	return STRING_SIZE;
}
//Number of char in string
int String::length() const {
	int length = 0;
	for (int i = 0; this->str[i] != '\0'; i++) {
		length++;
	}
	return length;
}
//Concatenation
String String::operator+(const String& s) const {
	String result;
	for (int i = 0; this->str[i] != '\0'; i++) {
		result.str[i] = this->str[i];
	}
	for (int i = 0; s.str[i] != '\0'; i++) {
		result.str[i + (this->length())] = s.str[i];
	}
	result.str[this->length() + s.length()] = '\0';
	return result;
}
bool String::operator== (const String& s) const {
	if (this->length() != s.length()) {
		return 0;
	}
	if (this->length() == s.length()) {
		for (int i = 0; this->str[i] != '\0'; i++) {
			if (this->str[i] != s.str[i]) {
				return 0;
			}
		}
		return 1;
	}
}
bool String::operator< (const String& s) const {
	return 0;
}
std::istream& operator>>(std::istream& in, String& s) {
	char str[256];
	int i = 0;
	in.getline(str, 256, '\n');
	while(str[i] != '\0') {
		if (str[i] == ' ') {
			s.str[i] = '\0';
			return in;
		}
		s.str[i] = str[i];
		i++;
	} s.str[i] = '\0';
	return in;
}
std::ostream& operator<<(std::ostream& out, const String& s) {
	for (int i = 0; s.str[i] != '\0'; i++) {
		out << s.str[i];
	}
	return out;
}
String  operator+  (const char str_one[], const String& str_two) {
	String result;
	int str_one_length = 1;
	for (int i = 0; str_one[i] != '\0'; i++) {
		result[i] = str_one[i];
		str_one_length++;
	}
	for (int i = 0; str_two[i] != '\0'; i++) {
		result[i + str_one_length] = str_two[i];
	}
	result[str_one_length + str_two.length()] = '\0';
	return result;
}
String  operator+  (char ch, const String& str) {
	String result;
	result[0] = ch;
	if (str[0] == '\0') {
		result[1] = '\0';
		return result;
	}
	else {
		for (int i = 0; str[i] != '\0'; i++) {
			result[i + 1] = str[i];
		} result[str.length() + 1] = '\0';
		return result;
	}
}
bool operator== (const char carr[], const String& s) {
	int carrLength = 0;
	for (int i = 0; carr[i] != '\0'; i++) {
		carrLength++;
	}
	if (carrLength - 1 != s.length()) {
		return 0;
	}
	if (carrLength == s.length()) {
		for (int i = 0; carr[i] != '\0'; i++) {
			if (carr[i] != s[i]) {
				return 0;
			}
		}
		return 1;
	}
}
bool operator== (char ch, const String& s) {
	if (s.length() != 1) {
		return 0;
	}
	if (s.length() == 1) {
		if (s[0] == ch) {
			return 1;
		}
		else {
			return 0;
		}
	}
}
bool operator<  (const char str_one[], const String& str_two) {
	for (int i = 0; str_one[i] != '\0' || str_two[i] != '0';) {
		if (str_one[i] == str_two[i]) {
			i++;
		}
		else if (str_one[i] < str_two[i]) {
			return 1;
		}
		else {
			return 0;
		}
	} return 0;
}
bool operator<  (char ch, const String& str) {
	if (str[0] == '\0') {
		std::cout << "Cannot meaningfully compare empty string";
		return 0;
	}
	if (ch < str[0]) {
		return 1;
	} return 0;
}
bool operator<= (const String& str_one, const String& str_two) {
	for (int i = 0; str_one[i] != '\0' && str_two[i] != '\0';) {
		if (str_one[i] == str_two[i]) {
			i++;
		}
		if (str_one[i] < str_two[i]) {
			return 1;
		}
		else {
			return 0;
		}
	}
	if (str_one.length() == str_two.length()) {
		return 1;
	}
}
bool operator!= (const String& str_one, const String& str_two) {
	if (str_one.length() == str_two.length()) {
		for (int i = 0; str_one[i] != '\0';) {
			if (str_one[i] == str_two[i]) {
				i++;
			}
			else {
				return 1;
			}
		} return 0;
	}
	else {
		return 0;
	}
}
bool operator>= (const String& str_one, const String& str_two) {
	for (int i = 0; str_one[i] != '\0' || str_two[i] != '\0';) {
		if (str_one[i] == str_two[i]) {
			i++;
		}
		if (str_one[i] > str_two[i]) {
			return 1;
		}
		else {
			return 0;
		}
	} return 1;
}
bool operator>  (const String& str_one, const String& str_two) {
	for (int i = 0; str_one[i] != '\0' || str_two[i] != '\0';) {
		if (str_one[i] == str_two[i]) {
			i++;
		}
		if (str_one[i] > str_two[i]) {
			return 1;
		}
		else {
			return 0;
		}
	} return 0;
}
/*
bool operator== (const char str_one[], const String& str_two) {
	int strOneLength = 0;
	for (int i = 0; str_one[i] != '\0'; i++) {
		strOneLength++;
	}
	if (strOneLength != str_two.length()) {
		return 0;
	}
	for (int i = 0; str_one[i] != '\0' || str_two[i] != '\0';) {
		if (str_one[i] == str_two[i]) {
			i++;
		}
		else {
			return 0;
		}
	} return 1;
}*/
String String::substr(int start, int end) {
	String aSubStr;
	for (int i = start; i <= end; i++) {
		aSubStr[i - start] = this->str[i];
	}aSubStr[(end - start) + 1] = '\0';
	return aSubStr;
}
//Returns location of ch at or after pos, returns -1 if not found
int String::findch(int pos, char ch) {
	for (int i = pos; this->str[i] != '\0'; i++) {
		if (this->str[i] == ch) {
			return i;
		}
	} return -1;
}
//Returns the location of str at or after pos, returns -1 if not found
int String::findstr(int pos, const String& str) {
	if (str[0] == '\0') {
		std::cout << "Cannot search for empty string" << "\n";
	}
	int i = 0;
	while (this->str[pos] != '\0') {
		if (this->str[pos] == str[i]) {
			if (str[i + 1] == '\0') {
				return (pos - i);
			}
			pos++;
			i++;
		}
		else {
			pos++;
			i = 0;
		}
	} return -1;
}