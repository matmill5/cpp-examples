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

	std::cout << "Done testing default constructor" << std::endl;



}