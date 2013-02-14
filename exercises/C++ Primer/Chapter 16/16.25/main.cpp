// Ex 16.25: explicit template arguments and string literals

#include <iostream>
#include <string>

template <class Type, class Other> bool compare(const Type &a, const Other &b)
{
	return (a < b);
}

int main()
{
	int i1 = 12, i2 = 13;
	short s1 = 1, s2 = 3;

	std::cout << compare(i1, i2) << std::endl;
	std::cout << compare(s1, s2) << std::endl;

	// change both types to int before comparing
	std::cout << compare<int, int>(i1, s2) << std::endl;

	// ex 16.25: giving reasonable (comparable) type to string literals
	std::cout << compare<const std::string>("abc", "def") << std::endl;

	return 0;
}
