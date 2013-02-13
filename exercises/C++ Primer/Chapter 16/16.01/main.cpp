// Ex 16.01: template functions

#include <iostream>
#include <string>

template <typename T> inline unsigned absolute(const T &a)
{
	if (a < 0)
		return -a;
	else
		return a;
}

int main()
{
	int a = -3;
	double b = 55;
	unsigned long c = 12000;

	std::cout << absolute(a) << " " << absolute(b) << " " << absolute(c) << std::endl;

	return 0;
}
