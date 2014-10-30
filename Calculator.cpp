#include "Calculator.h"


void Calculator :: readFile(const char* filename)
{

	fstream in(filename);
	if (!in)
	{
		throw "Error, cannot load file!";
	}

	// a counter used for counting how many operators have been loaded
	// from the file
	int opCounter = 0;

	// reading the data directly to the Oper struct
	while (in)
	{
		if (in.eof())
			break;
		in >> opers[opCounter].symbol;
		in >> opers[opCounter].operation;
		in >> opers[opCounter].priority;
		in >> opers[opCounter].asso;
		opCounter++;

	}

	in.close();

	// adding two exta operators 
	// for the parantheses
	opers[opCounter++].symbol = '(';
	opers[opCounter].symbol = ')';

	numberOfOperators = opCounter + 1;
}


double Calculator :: doOpCalc(double x, double y, Oper op)
{
	switch(op.operation)
	{
	case '+':
		return x + y;
		break;
	case '-':
		return x - y;
		break;
	case '*':
		return x * y;
		break;
	case '/':
		if ( y != 0)
		{
			return x / y;
			break;
		}
		else throw "Division by 0"; // error division by 0
		break;
	}
}

void Calculator :: doStackCalc(const Oper &current)
{
	while (true)
	{
		if (current.symbol == '(')
		{
			operations.push(current);
			break;
		}

		else if (current.symbol == ')')
		{
			char temp = operations.peek().symbol;

			while (temp != '(') 
			{
				numbers.push(doOpCalc(numbers.pop(),numbers.pop(),operations.pop()));
				temp = operations.pop().symbol;
			}
			break;
		}
		else if (operations.isEmpty() || current.HasHigherPriorThan(operations.peek()))
		{

			operations.push(current);
			break;
		}
		else 
		{
			// TO DO : check if there are two elements in the numb stack
			numbers.push(doOpCalc(numbers.pop(),numbers.pop(),operations.pop()));
		}
	}	
}

void Calculator :: doFinalStackCalc()
{

	while (!operations.isEmpty())
	{
		// TO DO : check if there are two elements in the numb stack
		numbers.push(doOpCalc(numbers.pop(),numbers.pop(),operations.pop()));
	}

	double temp = numbers.pop();

	if (!numbers.isEmpty())	
	{
		throw "The expression is not correct";
	}
	else
		numbers.push(temp);
}

bool Calculator :: ParenCheck(const char* expr)
{
	int parenCnt = 0;
	while (*expr)
	{
		if (*expr == '(')
		{
			parenCnt++;
		}
		if (*expr == ')')
			parenCnt--;
		expr++;
	}
	if (parenCnt != 0)
	{
		return false;
	}
	return true;
}

void Calculator :: calculateExpr(const char* expr)
{
	double result = 0;
	char* endPtr;

	if (!ParenCheck(expr))
	{
		throw "Expression is not correct";
	}

	while(*expr)
	{
		if (isspace(*expr))
		{
			expr++;
		}

		else if (isdigit(*expr) || (*expr == '-' && isdigit(*(expr+1))))
		{
			numbers.push(strtod(expr, &endPtr));
			expr = endPtr;
		}

		else
		{
			int opIndex = 0;

			while (opIndex < numberOfOperators)
			{

				if (opers[opIndex].symbol == *expr)
				{
					doStackCalc(opers[opIndex]);
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

	doFinalStackCalc();
	result = numbers.pop();

	cout << "Result : " << result << endl;
}