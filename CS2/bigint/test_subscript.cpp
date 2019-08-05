// bigint Test Program
//
// Tests:  subscript, uses ==
//
#include <iostream>
#include <cassert>
#include "bigint.hpp"

//Tests for substring
//===========================================================================

int main(){
		{
		// Setup
		bigint bi(4);

		// Test 
		int digit = bi[0];

		// Verify
		assert(bi == 4);
		assert(digit == '4');
		}

		{
			// Setup
			bigint bi(0);

			// Test 
			int digit = bi[0];
			int digit_one = bi[1];

			// Verify
			assert(bi == 0);
			assert(digit == '0');
			assert(digit_one == '0');
		}

		{
			// Setup
			bigint bi(8910111);

			// Test 
			int digit = bi[1];
			int digit_one = bi[2];

			// Verify
			assert(bi == 8910111);
			assert(digit == '1');
			assert(digit_one == '1');
		}

		{
			// Setup
			bigint bi(8910121);

			// Test 
			int digit = bi[0];
			int digit_one = bi[1];

			// Verify
			assert(bi == 8910121);
			assert(digit == '1');
			assert(digit_one == '2');
		}

		//Add test cases!!

		std::cout << "Done testing subscript." << std::endl;
}

