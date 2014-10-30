#include <iostream>
#include "Calculator.h"
using namespace std;


// NOTE TODO : check for associativity
// It doesnt check assotiativity of the operators
// 
int main(int argc, char *argv[])
{
	if ( argc != 3)
	{
		cout << "not enough parameters";
		return 1;
	}

	Calculator test;

	const char* filename = argv[1];
	const char* expression = argv[2];

	test.readFile(filename);
	try
	{
		test.calculateExpr(expression);
	}
	catch (char* param)
	{
		cout << "ERROR!" << endl;
		cout << param << endl;
	}
	return 0;
}