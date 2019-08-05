#ifndef CS2_UTILITIES_HPP_
#define CS2_UTILITIES_HPP_
////////////////////////////////////////////////////////////////////////////
//
// File: utilities.hpp
//
// Programmer:
// Updated:    3/2019
//
//
//
//

////////////////////////////////////////////////////////////////////////////
//  

#include <fstream>
#include "string.hpp"

void infixToPostFix(std::ifstream&, std::ofstream&);
void postFixToAsm(std::ifstream&, std::ofstream&);
String asmOperator(const String& op);

#endif