//Program to check the validity of the parentheses

#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "ParenChecker.h"
#include "Syntax_Error.h"

using namespace std;

const string leftParens = "{[(";      //string of left parens
const string rightParens = "}])";     //string of right parens
extern int leftCount = 0;             //initalizes the count for left parens
extern int rightCount = 0;            //initalizes the count for right parens
const string operators = "=, +, -, /, *, %, <, >, !, ^, >=, <=, &&, ||, ==, !=";

bool isBalanced(const string& expression){
	int leftCount = 0;             //initalizes the count for left parens
	int rightCount = 0;            //initalizes the count for right parens
	for (int i = 0; i < expression.size(); ++i){
		if (leftParens.find(expression[i])){
			leftCount++;
		}
		if (rightParens.find(expression[i])){
			rightCount++;
		}
	}
	if (leftCount == rightCount)
		return true;
	else
		return false;
}


