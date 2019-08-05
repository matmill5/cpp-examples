#include "stack.hpp"
#include "string.hpp"
#include <iostream>

int main(){

	{
		stack<String> test, result, newStack;
		String anItem("anItem");
		test.push(anItem);
		result = test;

		assert(test == result);
		assert(test != newStack);

		assert(test.getHeight() == 1);
		assert(result.getHeight() == 1);
		assert(newStack.getHeight() == 0);

		assert(test.pop() == "anItem");
		assert(test.getHeight() == 0);
	}

	{
		stack<int> test, result, newStack;
		int anItem = 100;
		test.push(anItem);
		result = test;

		assert(test == result);
		assert(test != newStack);

		assert(test.getHeight() == 1);
		assert(result.getHeight() == 1);
		assert(newStack.getHeight() == 0);

		assert(test.pop() == 100);
		assert(test.getHeight() == 0);
	}

	{
		stack<bool> test, result, newStack;
		bool anItem = false;
		test.push(anItem);
		result = test;

		assert(test == result);
		assert(test != newStack);

		assert(test.getHeight() == 1);
		assert(result.getHeight() == 1);
		assert(newStack.getHeight() == 0);

		assert(test.pop() == false);
		assert(test.getHeight() == 0);
	}

	std::cout << "Done testing test_push_pop" << '\n';
	return 0;
}
