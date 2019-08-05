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
		String a("abc");
		String b("dfghi");
		String result;

		// Test
		result = a + b;
		result = result.substr(3, 4);

		// Verify
		assert(a == "abc");
		assert(b == "dfghi");
		assert(result == "df");
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a('a');
		String b("bcdefg");
		String result;

		// Test
		result = a + b;
		result = result.substr(0, 5);

		// Verify
		assert(a == 'a');
		assert(b == "bcdefg");
		assert(result == "abcdef");
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a('9');
		String b('%');
		String result;

		// Test
		result = a + b;
		result = result.substr(0, 1);

		// Verify
		assert(a == '9');
		assert(b == '%');
		assert(result == "9%");
	}

	std::cout << "Done testing sub string" << std::endl;

}