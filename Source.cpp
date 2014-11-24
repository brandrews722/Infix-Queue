#include "ParenChecker.h"
#include "Syntax_Error.h"
#include "InfixEval.h"
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main(){
	string expression;
	cout << "What is the name of the file that you would like to read in?" << endl;
	cin >> expression;
	InfixEval evaluateFile;
	evaluateFile.readFile(expression);
	system("pause");
	return 0;
}
