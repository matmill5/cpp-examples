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
		int loc = 3;
		loc = result.findstr(0, "bcd");

		// Verify
		assert(a == 'a');
		assert(b == "bcdefghi");
		assert(result == "abcdefghi");
		assert(loc == 1);
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a('a');
		String b("bcdefghi");
		String result;

		// Test
		result = a + b;
		int loc = 1;
		loc = result.findstr(0, "def");

		// Verify
		assert(a == 'a');
		assert(b == "bcdefghi");
		assert(result == "abcdefghi");
		assert(loc == 3);
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a('a');
		String b("bcdefghi");
		String result;

		// Test
		result = a + b;
		int loc = 1;
		loc = result.findstr(5, "def");

		// Verify
		assert(a == 'a');
		assert(b == "bcdefghi");
		assert(result == "abcdefghi");
		assert(loc == -1);
	}

	std::cout << "Done testing find c-string" << std::endl;

}