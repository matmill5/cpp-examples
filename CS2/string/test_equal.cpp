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
		// Setup fixture
		String a('a');
		String b("bcdefghi");
		String result;

		// Test
		result = a + b;
		result = result[2];

		// Verify
		assert(a == 'a');
		assert(b == "bcdefghi");
		assert(result == "c");
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a('a');
		String b("bcdefghi");
		String result;

		// Test
		result = a + b;
		result[2] = 'f';

		// Verify
		assert(a == 'a');
		assert(b == "bcdefghi");
		assert(result == "abfdefghi");
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a('a');
		String b("bcdefghi");
		String result;

		// Test
		result = a + b;
		int resultLength = result.length();

		// Verify
		assert(a == 'a');
		assert(b == "bcdefghi");
		assert(result == "abcdefghi");
		assert(resultLength == 9);
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a('a');
		String b("bcdefghi");
		String result;

		// Test
		result = a + b;
		bool test = 1;
		test = (result == 'a');

		// Verify
		assert(a == 'a');
		assert(b == "bcdefghi");
		assert(result == "abcdefghi");
		assert(test == 0);
	}

	std::cout << "Done testing equals" << std::endl;

}