#include <iostream>
#include "Calculator.h"
using namespace std;


int main()
{
	Calculator test;
	test.readFile("op.txt");
	const char* buff = "5 a -6 b 3";
	try
	{
		test.calculateExpr(buff);
	}
	catch (char* param)
	{
		cout << "ERROR!" << endl;
		cout << param;
	}
	return 0;
}