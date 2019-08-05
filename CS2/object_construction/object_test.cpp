#include <iostream>
#include "object_construction.hpp"
#include <fstream>

int main(){
	myClass aMyClass;
	myClass aMyClass_one(aMyClass);
	aMyClass = aMyClass_one;
}
