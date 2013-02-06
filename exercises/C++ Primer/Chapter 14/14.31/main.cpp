// Ex 14.31: call overload

#include <iostream>
#include <string>

struct Conditional
{
	int operator() (bool condition, int firstParameter, int secondParameter);
};

int Conditional::operator() (bool condition, int firstParameter, int secondParameter)
{
	if (condition)
		return firstParameter;
	else
		return secondParameter;
}

int main()
{
	Conditional ifElse;

	std::cout << ifElse((1 == 4), 1, 0) << std::endl;
	std::cout << ifElse((1 != 4), 1, 0) << std::endl;

	return 0;
}
