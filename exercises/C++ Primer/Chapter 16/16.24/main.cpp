// Ex 16.24: explicit template arguments

#include <iostream>
#include <string>

template <class Type> bool compare(Type a, Type b)
{
	return (a < b);
}

int main()
{
	int i1 = 12, i2 = 13;
	short s1 = 1, s2 = 3;

	std::cout << compare(i1, i2) << std::endl;
	std::cout << compare(s1, s2) << std::endl;

	// this call would be an error without explicitly telling
	// the type we want to use in template function
	std::cout << compare<int>(i1, s2) << std::endl;

	return 0;
}
