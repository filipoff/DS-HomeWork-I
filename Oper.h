#pragma once

// a simple struct used for storing the information of a text file with operator atributes
struct Oper
{
	char symbol, operation;
	int priority, asso;
	Oper() : symbol('0'), operation('0'), priority(0), asso(0) {}
	
	// a function that checks if a given operator has higher priority than some other operator
	bool HasHigherPriorThan(const Oper &other) const;

};