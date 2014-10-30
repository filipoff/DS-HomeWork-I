#include "Oper.h"

bool Oper :: HasHigherPriorThan(const Oper &other) const
{
	if (symbol == '(' || symbol == ')')
		return true;
	else
		return priority > other.priority;
}
