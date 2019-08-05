#include "stack.hpp"
#include "string.hpp"
#include <iostream>

int main(){

	{
		stack<String> newStack;
		assert(newStack == stack<String>());
		assert(newStack.getHeight() == 0);

		newStack.push("A");
		newStack.push("B");
		newStack.push("C");

		stack<String> newerStack(newStack);
		
		assert(newStack == newerStack);
		assert(newerStack.pop() == "C");
		assert(newerStack.pop() == "B");
		assert(newerStack.pop() == "A");
	}

	{
		stack<int> newStack;
		assert(newStack == stack<int>());
		assert(newStack.getHeight() == 0);

		newStack.push(1);
		newStack.push(2);
		newStack.push(3);

		stack<int> newerStack(newStack);

		assert(newStack == newerStack);
		assert(newerStack.pop() == 3);
		assert(newerStack.pop() == 2);
		assert(newerStack.pop() == 1);
	}

	{
		stack<bool> newStack;
		assert(newStack == stack<bool>());
		assert(newStack.getHeight() == 0);

		newStack.push(false);
		newStack.push(true);
		newStack.push(true);

		stack<bool> newerStack(newStack);

		assert(newStack == newerStack);
		assert(newerStack.pop() == true);
		assert(newerStack.pop() == true);
		assert(newerStack.pop() == false);
	}

	std::cout << "Done testing copy_ctor" << '\n';
	return 0;
}
