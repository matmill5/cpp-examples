#pragma once

#include <iostream>

#ifndef BIGINT_H
#define BIGINT_H

const int CAPACITY = 200;

class bigint
{
public:
	bigint();
	bigint(int num);
	bigint(const char* digit);
	bigint times_digit(int num_times);
	bigint times_10(int num_10) const;
	void debugPrint(std::ostream&) const;
	int length();
	char &operator[](int);
	void operator = (int);
	int trailingZeros();
private:
	char bigintArr[CAPACITY];

	friend std::ostream& operator << (std::ostream& out, bigint b_i);

	friend bool operator == (bigint, bigint);

	friend bigint operator * (bigint, bigint);

	friend bigint operator + (bigint, bigint);

	friend std::istream& operator >> (std::istream&, bigint&);
};

#endif