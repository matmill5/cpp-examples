// bigint Test Program
//
// Tests:  times_10, uses ==
//
#include <iostream>
#include <cassert>
#include "bigint.hpp"

//===========================================================================
int main() {
	{
		//------------------------------------------------------
		// Setup fixture
		bigint bi(3);

		// Test 
		bi = bi.times_digit(1);

		// Verify
		assert(bi == 3);
	}

	{
		//------------------------------------------------------
		// Setup fixture
		bigint bi(38);

		// Test 
		bi = bi.times_digit(2);

		// Verify
		assert(bi == 76);
	}

	{
		//------------------------------------------------------
		// Setup fixture
		bigint bi(0);

		// Test 
		bi = bi.times_digit(20);

		// Verify
		assert(bi == 0);
	}

	{
		//------------------------------------------------------
		// Setup fixture
		bigint bi(99992);

		// Test 
		bi = bi.times_digit(10);

		// Verify
		assert(bi == 999920);
	}

	{
		//------------------------------------------------------
		// Setup fixture
		bigint bi(123456789);

		// Test 
		bi = bi.times_digit(1003);

		// Verify
		assert(bi == "123827159367");
	}

	{
		//------------------------------------------------------
		// Setup fixture
		bigint bi("999999999999999999999999");

		// Test 
		bi = bi.times_digit(10000);

		// Verify
		assert(bi == "9999999999999999999999990000");
	}


	//Add test cases as needed.

	std::cout << "Done testing bigint * digit" << std::endl;
}

