#include <iostream>
#include "Calculator.h"
using namespace std;


int main()
{
	Calculator test;
	test.readFile("op.txt");
	const char* buff = "-523 a -615";
	test.calculateExpr(buff);
	return 0;
}