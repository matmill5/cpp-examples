// fib_sequence.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

int Fibonacci(int);

int main()
{
	std::string user_input;
	std::cout << "Enter an index n: ";
	std::cin >> user_input;
	int n = stoi(user_input);
	for (int i = 0; i < n; i++) {
		std::cout << Fibonacci(i) << " ";
	}
}

int Fibonacci(int n) {
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}