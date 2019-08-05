#include <iostream>
#include "object_construction.hpp"

myClass::myClass(){
	std::cout << "Called Constructor" << '\n';
}
myClass::myClass(const myClass&){
	std::cout << "Called Copy Constructor" << '\n';
}
myClass::~myClass(){
	std::cout << "Called Destructor" << '\n';
}

void myClass::operator = (myClass) {
	std::cout << "Assignment Operator Called" << '\n';
}