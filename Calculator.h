#pragma once
#include <iostream>
#include "Oper.h"
#include "TemplateLinkedListStack.h"
#include <fstream>
using namespace std;


// maximum number of operators that can be read from file
// for a single char is 255 + 2 for the parantheses
const int MAX_OPERATORS = 257;

class Calculator
{
	// an array used for storing struct Oper, which is a structure of operators describes the
	// symbol priority associativity and the mathematical sign for the operators
	// read from the input file
	Oper opers[MAX_OPERATORS];


	// a stack used for storing struct Oper used for calculating the expresssion
	Stack <Oper> operations;


	// a stack used for storing numbers and used for calculating the expression
	Stack <double> numbers;

	// the current number of operators loaded from the file
	int numberOfOperators;

	// a help function that according to the math sign of the struct Oper
	// performs the math operation on two parameter numbers and returns a number as result
	double doOpCalc(double x, double y, Oper op);

	// a function that performs operations using both the number and the Oper stacks
	// takes an Oper struct as parameters
	void doStackCalc(const Oper &current);

	// similar to the previous function but makes the final calculation after the full
	// input expression is analyzed
	void doFinalStackCalc();

	// a function that checks if the expression has valid parantheses
	bool ParenCheck(const char* expr);

public:
	// a function that loads the operators from a text file
	void readFile(const char* filename);

	// the actual method that calculates the input expression
	void calculateExpr(const char* expr);
};