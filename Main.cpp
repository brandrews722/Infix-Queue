
/*#include <fstream>
#include "InfixEval.h"


int main()
{
	InfixEval InflixEvaluator;
	std::string expression;
	std::string answer;
	// Input/output files
	std::ifstream fin("input.txt");

	// Throw error if can't open input file
	if (!fin)
	{
		std::cerr << "Cannot open input file";
		system("pause");
		return 1;
	}

	while (fin.good())
	{
		getline(fin, expression);
		answer = InflixEvaluator.evaluate(expression);
		if (answer != "null"){
			std::cout << "Answer = " << answer;
		}
		std::cout << std::endl << std::endl;
	}

	system("pause");
	// Close files
	fin.close();
	return 0;
}*/