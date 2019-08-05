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
		std::cout << "Enter 'abc' to test cin input" << '\n';
		std::cin >> a;

		// Verify
		assert(a == "abc");
		assert(b == 'b');
	}
	{
		//-----------------------------------------------------
		// Setup fixture

		String a('a');
		String b('b');

		//Test
		std::cout << "Enter '998!' to test cin input" << '\n';
		std::cin >> a;

		// Verify
		assert(a == "998!");
		assert(b == 'b');
	}

	std::cout << "Done testing input" << std::endl;

}