// CS2_Project1_bigint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>
#include "bigint.hpp"

//Default constructor
bigint::bigint() {
	for (int i = 0; i < CAPACITY; i++) {
		bigintArr[i] = '0';
	}
}
//Int Constructor
bigint::bigint(int num) : bigint() {
	int i = 0;

	//num to bigintArr
	while (num > 0)
	{
		bigintArr[i] = '0' + (num % 10);
		num = num / 10;
		i++;
	}

	//Remaining elements to 0
	for (; i < CAPACITY; ++i)
		bigintArr[i] = '0';
}
//Char constructor
bigint::bigint(const char* digit) : bigint() {
	int i = 0;
	
	//Reads the characters until null val
	while (digit[i] != '\0') {
		if (strlen(digit) > 200) {
			std::cout << "Exceeded bigint capacity of 200." << '\n';
			break;
		}
		bigintArr[i] = digit[((strlen(digit) - 1) - i)];
		i++;
	}
	while (i < CAPACITY) {
		bigintArr[i] = '0';
		i++;
	}
}
//Operator overload
std::ostream& operator << (std::ostream& out, bigint b_i) {
	int leading_zero_counter = 0;
	int digit_per_line_counter = 0;

	for (int i = 199; b_i.bigintArr[i] == '0'; i--) {
		leading_zero_counter++;
	}
	for (int i = (199 - leading_zero_counter); i >= 0; i--) {
		if (digit_per_line_counter == 80) {
			out << '\n';
			digit_per_line_counter = 0;
		}
		out << b_i.bigintArr[i];
		digit_per_line_counter++;
	}
	return out;
}

std::istream& operator >> (std::istream& in, bigint& b_i_one) {
	char str[256];
	int input_size = 0;

	in.getline(str, 256, ';');

	while (str[input_size] != '\0') {
		if (str[input_size] == '\n') {
			input_size++;
			continue;
		}
		if (str[input_size] == ' ') {
			input_size++;
			continue;
		}
		b_i_one.bigintArr[strlen(str) - (input_size + 1)] = str[input_size];
		input_size++;
	}
	return in;
}
//Operator overload
bool operator == (bigint b_i_one, bigint b_i_two) {
	for (int i = 0; i < CAPACITY; i++) {
		if (b_i_one.bigintArr[i] != b_i_two.bigintArr[i])
		{
			return false;
		}
	}
	return true;
}
//
bigint operator * (bigint b_i_one, bigint b_i_two) {
	bigint tmp;

	bigint product;

	for (int i = 0; i < CAPACITY - 1; i++) {
		tmp = b_i_one.times_digit(b_i_two.bigintArr[i] - '0');
		product = product + tmp.times_10(i);
	}
	return product;
}
//Addition overload
bigint operator + (bigint b_i_one, bigint b_i_two) {
	bigint tmp;
	int result = 0;
	int result_firstDigit = 0;
	int result_secondDigit = 0;
	int carryCounter = 0;

	for (int i = 0; i <= CAPACITY - 1; i++) {
		result = (b_i_one.bigintArr[i] - '0') + (b_i_two.bigintArr[i] - '0') + result_secondDigit;
		if (result > 9) {
			result_firstDigit = result % 10;
			result_secondDigit = result / 10;
			tmp.bigintArr[i] = result_firstDigit + '0';
			carryCounter++;
		}
		else {
			result_secondDigit = 0;
			tmp.bigintArr[i] = result + '0';
		}
	}
	if (carryCounter >= 200) {
		return bigint("OVERFLOW");
	}
	return tmp;
}
char &bigint::operator [] (int i) {
	if (i > CAPACITY - 1){
		std::cout << "Array index out of bounds";
		exit(0);
	}
	return bigintArr[i];
}
//
int bigint::length() {
	int lengthCount = 0;
	for (int i = CAPACITY - 1; i >= 0; i--) {
		if (bigintArr[i] == '0') {
			lengthCount++;
		}
		else {
			return (CAPACITY - lengthCount);
		}
	}
}
//Debug print to stream
void bigint::debugPrint(std::ostream& aStream) const {
	for (int i = CAPACITY - 1; i >= 0; i--) {
		aStream << bigintArr[i] << '|';
	}
}

void bigint::operator = (int num) {
	int i = 0;

	//num to bigintArr
	while (num > 0)
	{
		bigintArr[i] = '0' + (num % 10);
		num = num / 10;
		i++;
	}

	//Remaining elements to 0
	for (; i < CAPACITY; ++i)
		bigintArr[i] = '0';
}

bigint bigint::times_digit(int num_times) {
	bigint tmp;
	tmp = *this;
	bigint result;
	for (int i = 0; i < num_times; i++) {
		result = tmp + result;
	}
	return result;
}
bigint bigint::times_10(int num_10) const {
	bigint tmp;
	for (int i = 0; i < CAPACITY - num_10 - 1; i++) {
		tmp.bigintArr[i + num_10] = bigintArr[i];
	}
	for (int i = 0; i < num_10; i++) {
		tmp.bigintArr[i] = '0';
	}
	return tmp;
}
int bigint::trailingZeros() {
	int zeroCounter = 0;
	for (int i = CAPACITY - 1; i >= 0; i--) {
		if (this->bigintArr[i] == '0') {
			zeroCounter++;
		}
		if (this->bigintArr[i] != '0') {
			zeroCounter = 0;
		}
	}
	if (zeroCounter == 200) {
		return 0;
	}
	return zeroCounter;
}