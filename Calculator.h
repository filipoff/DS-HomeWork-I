#pragma once
#include <iostream>
#include "Oper.h"
#include "TemplateLinkedListStack.h"
#include <fstream>
using namespace std;

const int MAX_OPERATORS = 30;
class Calculator
{
	Stack <double> numbers;
	Stack <Oper> operations;
	Oper opers[MAX_OPERATORS];
	bool isOpSymbol(char c);
	int getNumberLen(int number) const;
	int findIntFromStr(char* str) const;
	double doOpCalc(int x, int y, Oper op);
public:
	void readFile(const char* filename);
	void calculateExpr(const char* expr);
};