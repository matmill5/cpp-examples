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
		String a("abcd");
		String b("efghi");
		String result;

		// Test
		result = a + b;

		// Verify
		assert(a == "abcd");
		assert(b == "efghi");
		assert(result == "abcdefghi");
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a("12345");
		String b("6789!");
		String result;

		// Test
		result = a + b;

		// Verify
		assert(a == "12345");
		assert(b == "6789!");
		assert(result == "123456789!");
	}
	{
		//-----------------------------------------------------
		// Setup fixture
		String a("9%^6f");
		String b("890_");
		String result;

		// Test
		result = a + b;

		// Verify
		assert(a == "9%^6f");
		assert(b == "890_");
		assert(result == "9%^6f890_");
	}

	std::cout << "Done testing char array constructor" << std::endl;

}