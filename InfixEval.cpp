#include "InfixEval.h"
#include "ParenChecker.h"



void InfixEval::readFile(string fileName)
{
	ifstream readIn;
	readIn.open(fileName);
	while (readIn.good())
	{
		string expression;
		getline(readIn, expression);
		int num = parseExpression(expression);
		cout << expression << " = " << num << endl;
	}
}

int InfixEval::evaluate()
{
	if (operatorStack.top() == "!")
	{
		string operatorValue = operatorStack.top();
		operatorStack.pop();
		int lhs = operandStack.top();
		operandStack.pop();
		int rhs = 0;
		infixEvalOp(operatorValue, lhs, rhs);
		return operandStack.top();
	}
	else{
		int lhs, rhs;
		string operatorValue;
		operatorValue = operatorStack.top();
		operatorStack.pop();
		rhs = operandStack.top();
		operandStack.pop();
		lhs = operandStack.top();
		operandStack.pop();
		infixEvalOp(operatorValue, lhs, rhs);
		return operandStack.top();
	}
}
int InfixEval::parseExpression(string& expression){
	string temp;
	deleteSpaces(expression);
	bool prevIsOper;
	if (isBalanced(expression)){
		//iterate through string
		for (int i = 0; i < expression.size();){
				if (expression[0] == '!' && isdigit(expression[1]) == true)
				{
					temp += expression[0];
					operatorStack.push(temp);
					++i;
					temp.clear();
					while (isdigit(expression[i]))
					{
						temp += expression[i];
						++i;
					}
					operandStack.push(stoi(temp));
					temp.clear();
				}
				else if (expression[i] == '!' && isdigit(expression[i + 1]))
				{
					temp += expression[i];
					operatorStack.push(temp);
					++i;
					temp.clear();
					while (isdigit(expression[i]))
					{
						temp += expression[i];
						++i;
					}
					operandStack.push(stoi(temp));
					temp.clear();
				}

				//check for negativity
				else if (expression[0] == '-' && isdigit(expression[1])){
					temp += expression[0];
					++i;
					while (isdigit(expression[i])){
						temp += expression[i];
						++i;
					}
					operandStack.push(stoi(temp));
					temp.clear();
				}

				else if (!isdigit(expression[i]) && expression[i + 1] == '-') //checks if there are two operators next to each other
				{
					temp += expression[i];
					operatorStack.push(temp);
					++i;
					temp.clear();;
					temp += expression[i];
					++i;
					while (isdigit(expression[i])){
						temp += expression[i];
						++i;
					}
					operandStack.push(stoi(temp));
					temp.clear();

				}
				else if (expression[i] == ')' && expression[i + 1] != NULL)
				{
					while (operatorStack.top() != "(")
						evaluate();
					operatorStack.pop();
					++i;
				}
				else if (!isdigit(expression[i]) && !isdigit(expression[i + 1]) && expression[i+1] != NULL)
				{
					if (((expression[i] == '>' || expression[i] == '<') && expression[i + 1] == '=')
						|| (expression[i] == '=' && expression[i + 1] == '=')
						|| (expression[i] == '&' && expression[i + 1] == '&')
						|| (expression[i] == '|' && expression[i + 1] == '|')
						|| (expression[i] == '!' && expression[i + 1] == '='))
					{
						temp = "";
						temp += expression[i];
						++i;
						temp += expression[i];
						++i;
						operatorStack.push(temp);
						temp.clear();
					}
				}

				else if (expression[i] == '-' && isdigit(expression[i + 1])){
					temp += expression[i];
					++i;
					//get negative number
					while (isdigit(expression[i]))
					{
						temp += expression[i];
						i++;
					}
					prevIsOper = false;
					operandStack.push(stoi(temp));
					temp.clear();
				}
				//if not negative get the number
				else if (isdigit(expression[i])){
					while (isdigit(expression[i])){
						temp += expression[i];
						++i;
					}
					operandStack.push(stoi(temp));
					temp.clear();
				}

				//otherwise the char is an operator
				else if (!isdigit(expression[i])){
					const string OPERATORS = "=, +, -, /, *, %, <, >, !, ^";
					const map<string, int>PRECEDENCE = { { "==", 1 }, { "!=", 1 }, { "&&", 2 }, { "||", 2 },
					{ ">", 3 }, { ">=", 3 }, { "<", 3 }, { "<=", 3 }, { "+", 4 }, { "-", 4 }, { "*", 5 }, { "/", 5 },
					{ "%", 5 }, { "^", 6 }, { "!", 7 } };
					/*if (expression[i] == '(')
					{
						temp = "";
						temp += expression[i];
						operatorStack.push(temp);
						++i;
						temp.clear();
					}*/
					if (expression[i] == ')'){
						while (operatorStack.top() != "(")
						{
							evaluate();
						}
						operatorStack.pop(); //pops the left paren
						++i;
						break;

					}
					if (OPERATORS.find(expression[i])){
						temp = "";
						temp += expression[i];
						if (operatorStack.empty() == true)
						{
							operatorStack.push(temp);
							temp.clear();
							++i;
						}
						else if (operatorStack.top() == "(")
						{
							operatorStack.push(temp);
							temp.clear();
							++i;
						}
						else if (PRECEDENCE.at(temp) > PRECEDENCE.at(operatorStack.top())){
							operatorStack.push(temp);
							temp.clear();
							++i;
						}
						else if (PRECEDENCE.at(temp) <= PRECEDENCE.at(operatorStack.top())){

							while (PRECEDENCE.at(temp) <= PRECEDENCE.at(operatorStack.top())){
								evaluate();
								if (operatorStack.empty())
									break;
							}

							operatorStack.push(temp);
							temp.clear();
							++i;
						}
					}
					prevIsOper = true;
				}
			}
	}
	else
		throw logic_error("Expression is invalid");
	while (!operatorStack.empty()){
		evaluate();
	}
	return operandStack.top();
}

//performs operations based on the operator passed in
void InfixEval::infixEvalOp(string op, int lhs, int rhs)
{
	
	int result = 0;

	if (op == "!"){
		result = (!lhs);
		operandStack.push(result);
	}
	else if (op == "^"){
		result = (int)(pow(lhs, rhs));
		operandStack.push(result);
	}
	else if (op == "+"){
		result = lhs + rhs;
		operandStack.push(result);
	}
	else if (op == "-"){
		result = lhs - rhs;
		operandStack.push(result);
	}
	else if (op == "*"){
		result = lhs * rhs;
		operandStack.push(result);
	}
	else if (op == "/"){
		result = lhs / rhs;
		operandStack.push(result);
	}
	else if (op == "%"){
		result = lhs % rhs;
		operandStack.push(result);
	}
	else if (op == ">"){
		result = (lhs > rhs);
		operandStack.push(result);
	}
	else if (op == ">="){
		result = (lhs >= rhs);
		operandStack.push(result);
	}
	else if (op == "<")
	{
		result = (lhs < rhs);
		operandStack.push(result);
	}
	else if (op == "<="){
		result = (lhs <= rhs);
		operandStack.push(result);
	}
	else if (op == "&&"){
		result = (lhs && rhs);
		operandStack.push(result);
	}
	else if (op == "||")
	{
		result = (lhs || rhs);
		operandStack.push(result);
	}
	else if (op == "=="){
		result = (lhs == rhs);
		operandStack.push(result);
	}
	else if (op == "!="){
		result = (lhs != rhs);
		operandStack.push(result);
	}

}
void InfixEval::deleteSpaces(string &str)
{
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}
