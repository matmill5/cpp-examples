// bigint Test Program
//
// Tests:  times_10, uses ==
//
#include <iostream>
#include <cassert>
#include "bigint.hpp"

//===========================================================================
int main () {
    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi(3);

        // Test 
        bi = bi.times_10(0);

        // Verify
        assert(bi == 3);
    }

	{
		//------------------------------------------------------
		// Setup fixture
		bigint bi(22);

		// Test 
		bi = bi.times_10(5);

		// Verify
		assert(bi == 2200000);
	}

	{
		//------------------------------------------------------
		// Setup fixture
		bigint bi(678);

		// Test 
		bi = bi.times_10(10);

		// Verify
		assert(bi == "6780000000000");
	}

	{
		//------------------------------------------------------
		// Setup fixture
		bigint bi(33);

		// Test 
		bi = bi.times_10(8);

		// Verify
		assert(bi == "3300000000");
	}

	{
		//------------------------------------------------------
		// Setup fixture
		bigint bi(89);

		// Test 
		bi = bi.times_10(42);

		// Verify
		assert(bi == "89000000000000000000000000000000000000000000");
	}

	{
		//------------------------------------------------------
		// Setup fixture
		bigint bi(3);

		// Test 
		bi = bi.times_10(0);

		// Verify
		assert(bi == 3);
	}

	{
		//------------------------------------------------------
		// Setup fixture
		bigint bi(92);

		// Test 
		bi = bi.times_10(3);

		// Verify
		assert(bi == 92000);
	}

    //Add test cases as needed.

    std::cout << "Done testing times_10" << std::endl;
}

