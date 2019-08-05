#include "stack.hpp"
#include "string.hpp"
#include <iostream>

int main(){

	{
		stack<String> newStack;
		assert(newStack == stack<String>());
		assert(newStack.getHeight() == 0);
	}

	{
		stack<int> newStack;
		assert(newStack == stack<int>());
		assert(newStack.getHeight() == 0);
	}

	{
		stack<bool> newStack;
		assert(newStack == stack<bool>());
		assert(newStack.getHeight() == 0);
	}

	std::cout << "Done testing ctor_default" << '\n';
	return 0;
}
