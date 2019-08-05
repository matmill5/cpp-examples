//  String Test Program
//
//  Tests:
//
//

#include <iostream>
#include <cassert>
#include "string.hpp"

//===========================================================================
int main() {

	{
		//-----------------------------------------------------
		// Test:
		// Setup fixture
		String a('9');
		String b(' ');
		String result;

		// Test
		result = a + b;

		// Verify
		assert(a == "9");
		assert(b == " ");
		assert(result == "9 ");
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a('a');
		String b('b');
		String result;

		// Test
		result = a + b;
		std::cout << "x" << a << "x";
		std::cout << b;
		std::cout << result;
		// Verify
		assert(a == "a");
		assert(b == "b");
		assert(result == "ab");
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a('9');
		String b('%');
		String result;

		// Test
		result = a + b;

		// Verify
		assert(a == "9");
		assert(b == "%");
		assert(result == "9%");
	}

	std::cout << "Done testing char constructor" << std::endl;

}
