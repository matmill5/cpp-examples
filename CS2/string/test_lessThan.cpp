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
		String b('b');

		// Test
		bool result = 1;
		result = b < a;

		// Verify
		assert(a == 'a');
		assert(b == 'b');
		assert(result == 0);
	}
	{
		//-----------------------------------------------------
		// Setup fixture

		String a('b');
		String b('a');

		// Test
		bool result = 0;
		result = b <= a;

		// Verify
		assert(a == 'b');
		assert(b == 'a');
		assert(result == 1);
	}
	{
		//-----------------------------------------------------
		// Setup fixture

		String a('b');
		String b('a');

		// Test
		bool result = 0;
		result = b <= a;

		// Verify
		assert(a == 'b');
		assert(b == 'a');
		assert(result == 1);
	}
	{
		//-----------------------------------------------------
		// Setup fixture

		String a('a');
		String b('b');

		// Test
		bool result = 1;
		result = b <= a;

		// Verify
		assert(a == 'a');
		assert(b == 'b');
		assert(result == 0);
	}

	std::cout << "Done testing less-than, great-than, less-than equals, greater-than equals" << std::endl;

}