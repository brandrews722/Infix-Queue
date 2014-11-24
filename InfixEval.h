#ifndef INFIXEVAL_H_
#define INFIXEVAL_H_

#include <istream>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstring>
#include <stack>
#include <sstream>
#include <cctype>
#include "Syntax_Error.h"
#include <map>
#include <fstream>

using namespace std;
class InfixEval{

private:
	stack<string> operatorStack;
	stack<int> operandStack;
	const string OPERATORS;
	const map < string, int > PRECEDENCE;//map will be used to check precedence of operators
	void InfixEval::infixEvalOp(string op, int lhs, int rhs);
	int evaluate();
	//int evaluate(string& expression);
	void deleteSpaces(string &str);
	int parseExpression(string& expression);

public:
	//performs operations based on the operator passed in
	InfixEval(){ ; }
	
	void readFile(string fileIn);
};
#endif 