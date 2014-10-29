#pragma once

// left = 0
// right = 1

struct Oper
{
	char symbol, operation;
	int priority, associativity;
	Oper() : symbol('0'), operation('0'), priority(0), associativity(0) {}
	Oper(const char symbol, const char operation, const int priority, const int associativity) : 
		symbol(symbol), operation(operation), priority(priority), associativity(associativity) {}
	bool opCompare(const Oper &other)
	{
		if (this->priority > other.priority)
		{
			return true;
		}
		else if (this->priority == other.priority)
		{
			if (associativity != other.associativity)
			{
			}
			// error;
		}

		return false;
	}

};