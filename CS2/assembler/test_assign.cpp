#include "stack.hpp"
#include "string.hpp"
#include <cassert>

int main() {
	
	{
		stack<String> test, result, newStack;
		String item[5];
		item[0] = "This";
		item[1] = "Is";
		item[2] = "A";
		item[3] = "Stack";
		item[4] = "With Items";
		for (int i = 0; i < 5; ++i) {
			test.push(item[i]);
		}

		result = test;
	
		assert(test == result);
		assert(test != newStack);
		assert(test.getHeight() == 5);
		assert(result.getHeight() == 5);
	}

	{
		stack<int> test, result, newStack;
		int item[5];
		item[0] = 12345;
		item[1] = 67890;
		item[2] = 22334;
		item[3] = 55667;
		item[4] = 99999;
		for (int i = 0; i < 5; ++i) {
			test.push(item[i]);
		}

		result = test;

		assert(test == result);
		assert(test != newStack);
		assert(test.getHeight() == 5);
		assert(result.getHeight() == 5);
	}

	{
		stack<bool> test, result, newStack;
		bool item[5];
		item[0] = true;
		item[1] = false;
		item[2] = true;
		item[3] = false;
		item[4] = true;
		for (int i = 0; i < 5; ++i) {
			test.push(item[i]);
		}

		result = test;

		assert(test == result);
		assert(test != newStack);
		assert(test.getHeight() == 5);
		assert(result.getHeight() == 5);
	}
	std::cout << "Done testing assign" << '\n';
	
	 return 0;	
}
