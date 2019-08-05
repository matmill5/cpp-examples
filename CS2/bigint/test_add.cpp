// bigint Test Program
//
// Tests:  int constructor, uses ==
//
#include <iostream>
#include <cassert>
#include "bigint.hpp"


//===========================================================================
int main() {

		// VERY INCOMPLETE set of tests.
	{
		//------------------------------------------------------
		// Setup fixture
		bigint left(0);
		bigint right(0);
		bigint result;

		// Test 
		result = left + right;

		// Verify
		assert(left == 0);
		assert(right == 0);
		assert(result == 0);

	}
	{
		//------------------------------------------------------
		// Setup fixture
		bigint left(1);
		bigint right(0);
		bigint result;

		// Test
		result = left + right;

		// Verify
		assert(left == 1);
		assert(right == 0);
		assert(result == 1);
	}
	{
		//------------------------------------------------------
		// Setup fixture
		bigint left(1);
		bigint right(1);
		bigint result;

		// Test
		result = left + right;

		// Verify
		assert(left == 1);
		assert(right == 1);
		assert(result == 2);
	}
	{
		// ------------------------------------------------------
		// Setup fixture
		bigint left("9");
		bigint right("5");
		bigint result;

		// Test
		result = left + right;

		// Verify
		assert(left == 9);
		assert(right == 5);
		assert(result == 14);
	}
	{
		//------------------------------------------------------
		//Class 0 Test
		bigint left_zero(0);
		bigint right_zero("0");

		// Test
		bigint result = left_zero + right_zero;

		// Verify
		assert(left_zero == 0);
		assert(right_zero == 0);
		assert(result == 0);
	}
	{
		//------------------------------------------------------
		//Testing for carry from addition of large numbers
		//Class Carry/OVERFLOW Test
		bigint left_carry("99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
		bigint right_carry("1");

		// Test
		bigint result = left_carry + right_carry;

		// Verify
		assert(left_carry == "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
		assert(right_carry == 1);
		assert(result == "OVERFLOW");
	}
	{
		//------------------------------------------------------
		//Testing six classes of bigints
		//Class test 0, 1-9 , ... , 10000-99999
		for (int j = 2; j <= 20000; j = j * 10) {
			bigint left_class(j);
			bigint right_class(j + 25);
			bigint result = left_class + right_class;

			assert(left_class == j);
			assert(right_class == (j + 25));
			assert(result == left_class + right_class);
		}

	}
		//Add test cases as needed.
    
    
    std::cout << "Done with testing addition." << std::endl;
}

