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
}
/*
int Calculator :: findIntFromStr(char* str) const
{
int cnt = 0;
char* startIntPtr = NULL;
char* endIntPtr = NULL;
int number = 0;
while(*str)
{
if (isdigit(str[cnt]))
{
startIntPtr = str + cnt;
while (isdigit(str[cnt]))
{
cnt++;
}
endIntPtr = str + cnt;
}
number = atoi(startIntPtr);
return number;
}
}
*/

bool Calculator :: isOpSymbol(char ch)
{
	const char* notOpSymbols = "()- ";
	return strchr(notOpSymbols,ch) == NULL;
}
int Calculator :: getNumberLen(int number) const
{
	if (number < 0)
	{
		number *= -1;
	}
	return (int)log10(number)+1;
}

double Calculator :: doOpCalc(int x, int y, Oper op)
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
		else throw "error"; // error division by 0
	}
}

void Calculator :: calculateExpr(const char* expr)
{
	int temp;
	while(*expr)
	{
		if (*expr == ' ')
		{
			expr++;
			continue;
		}
		else if (isdigit(*expr))
		{
			temp = atoi(expr);
			expr += getNumberLen(temp);
			numbers.push(temp);
			expr++;
			continue;
		}

		else if (*expr == '-' && isdigit(*(expr+1)))
		{
			temp = atoi(expr);
			expr += getNumberLen(temp) + 1; // for the minus
			numbers.push(temp);
			expr++;
			continue;
		}
		else if (isOpSymbol(*expr))
		{
			int cnt = 0;
			bool flag = false;
			while (cnt < MAX_OPERATORS)
			{
				if (opers[cnt].symbol == *expr)
				{
					flag = true;
					operations.push(opers[cnt]);
					break;
				}
				else
					cnt++;
			}
			if (!flag)
			{
				throw "error"; // invalid op symbol
			}
			while (!operations.isEmpty())
			{
				Oper op = operations.peek();

				if (op.priority < opers[cnt].priority)
					break;
				else
				{
					numbers.push(doOpCalc(numbers.pop(),numbers.pop(),operations.pop()));
				}
				operations.push(opers[cnt]);

			}
			expr++;
			continue;
		}
		expr++;
	}
}