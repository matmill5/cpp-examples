//  String Test Program
//
//  Tests:
//
//

#include <iostream>
#include <cassert>
#include "string.hpp"

//===========================================================================
int main () {

	{
		//-----------------------------------------------------
		// Test:
		// Setup fixture
		String a;
		String b;
		String result;

		// Test
		result = a + b;

		// Verify
		assert(a == "");
		assert(b == "");
		assert(result == "");
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a('a');
		String b("b");
		String result;

		// Test
		result = a + b;

		// Verify
		assert(a == 'a');
		assert(b == "b");
		assert(result == "ab");
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a('a');
		String b("bc");
		String result;

		// Test
		result = a + b;

		// Verify
		assert(a == 'a');
		assert(b == "bc");
		assert(result == "abc");
	}

	std::cout << "Done testing concat" << std::endl;

}