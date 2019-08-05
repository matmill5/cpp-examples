// CS2_Project3_Milestone2:  This file converts infix to postfix
//

#include "utilities.hpp"
#include "stack.hpp"
#include "string.hpp"

void infixToPostFix(std::ifstream& in, std::ofstream& out) {
	stack<String> theStack;
	String lhs, rhs, op, token;

	while (in >> token) {
		//in >> token;
		while (token != ";") {
			if (token == ")") {
				rhs = theStack.pop();
				op = theStack.pop();
				lhs = theStack.pop();
				theStack.push(lhs + rhs + op);
			}
			else if (token != "(") {
				theStack.push(token + ' ');
			}
			in >> token;
		}
		if (!out) { std::cout << theStack.top() << "\n"; }
		out << theStack.top() << std::endl;
	}
}

void postFixToAsm(std::ifstream& in, std::ofstream& out) {
	stack<String> theStack;
	String lhs, rhs, op, tmp, token;

	int tmpN = 1;

	while (!in.eof() || !theStack.empty()) {
		if (!in.eof()) {
			in >> token;
		}
		else {
			break;
		}

		if (in.peek() == '\n') {
			out << "==============" << std::endl;
			tmpN = 1;
		}

		if (!in.eof() && token != "+" && token != "-" && token != "*" && token != "/") {
			theStack.push(token);
		}
		else if (!in.eof()) {
			rhs = theStack.pop();
			lhs = theStack.pop();

			out << "LD\t" << lhs << std::endl;

			op = asmOperator(token);

			out << op << rhs << std::endl;

			if (tmpN == 1) {
				tmp = "TMP1";
				tmpN++;
			} else if(tmpN == 2) {
				tmp = "TMP2";
				tmpN++;
			}
			else if (tmpN == 3) {
				tmp = "TMP3";
				tmpN++;
			}
			else if (tmpN == 4) {
				tmp = "TMP4";
				tmpN++;
			}

			theStack.push(tmp);

			out << "ST\t" << tmp << std::endl;
		}
	}
}

String asmOperator(const String& op)
{
	switch (op[0]) {
	case '+':
		return "AD\t";
		break;
	case '-':
		return "SB\t";
		break;
	case '*':
		return "MU\t";
		break;
	case '/':
		return "DV\t";
		break;
	default:
		return "UNDEFINED\t";
	}
}
