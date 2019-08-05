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

		//Test
		int i = a.length();
		int z = a.capacity();
		std::cout << z;

		// Verify
		assert(i == 1);
		assert(b == 'b');
		assert(z != 256);
		assert(z == 1);
	}
	{
		//-----------------------------------------------------
		// Setup fixture

		String a("abc");
		String b('b');

		//Test
		int i = a.length();
		int z = a.capacity();

		// Verify
		assert(i == 3);
		assert(b == 'b');
		assert(z == 3);
	}

	std::cout << "Done testing length() capacity()" << std::endl;

}