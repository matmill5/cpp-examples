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

		String a("98thea");
		String b('b');
		String result;
		
		//Test
		result = a + b;
		int i = result.findch(0,'a');

		// Verify
		assert(a == "98thea");
		assert(b == 'b');
		assert(i == 5);
	}
	{
		//-----------------------------------------------------
		// Setup fixture

		String a("98thea");
		String b('b');
		String result;

		//Test
		result = a + b;
		int i = result.findch(0,'9');

		// Verify
		assert(a == "98thea");
		assert(b == 'b');
		assert(i == 0);
	}

	std::cout << "Done testing find char" << std::endl;

}