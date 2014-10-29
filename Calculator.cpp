#include "Calculator.h"


void Calculator :: readFile(const char* filename)
{

	fstream in(filename);
	if (!in)
		return; // more info

	int opCounter = 0;
	while (in)
	{
		in >> opers[opCounter].symbol;
		in >> opers[opCounter].operation;
		in >> opers[opCounter].priority;
		in >> opers[opCounter].associativity;
		opCounter++;
	}
	in.close();
	numberOfOperators = opCounter;
}

bool Calculator :: isOpSymbol(char ch)
{
	const char* notOpSymbols = "()- ";
	return strchr(notOpSymbols,ch) == NULL;
}

double Calculator :: doOpCalc(double x, double y, Oper op)
{
	switch(op.operation)
	{
	case '+':
		return y + x;
		break;
	case '-':
		return y - x;
		break;
	case '*':
		return y * x;
		break;
	case '/':
		if ( x != 0)
		{
			return y / x;
			break;
		}
		else throw "error"; // error division by 0
	}
}

void Calculator :: calculateExpr(const char* expr)
{
	double temp = 0;
	double result = 0;
	int opIndex = 0;
	char* endPtr;

	while(*expr)
	{
		if (isspace(*expr))
		{
			expr++;
		}

		else if (isdigit(*expr) || (*expr == '-' && isdigit(*(expr+1))))
		{
			temp = strtod(expr, &endPtr);
			expr = endPtr;
			numbers.push(temp);
		}

		// if is '(' push it to the op stack
		// if its ')' do operations until '(' is found
		// 

		else
		{
			while (opIndex < numberOfOperators)
			{
				if (opers[opIndex].symbol == *expr)
				{
					while (true)
					{
						if (operations.isEmpty() || opers[opIndex].opCompare(operations.peek()))
						{
							operations.push(opers[opIndex]);
							break;
						}
						else 
						{
							// TO DO : check if there are two elements in the numb stack
							numbers.push(doOpCalc(numbers.pop(),numbers.pop(),operations.pop()));
						}
					}
					break;
				}
				else
					opIndex++;
			}

			if (opIndex == numberOfOperators)
			{
				throw "error"; // invalid op symbol
			}
			expr++;

		}
	}
	// TO DO op stack must be empty
	// number stack only one number = the result
	result = numbers.peek();
	cout << "Result : " << result << endl;
}