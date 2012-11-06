// Ex 1.17 : Negative numbers

#include <iostream>

int main()
{
	std::cout << "Give a series of numbers, please." << std::endl;

	int negative = 0, value;
	while (std::cin >> value)
	{
		if (value < 0) 
		{
			++negative;
		}
	}

	std::cout << negative << std::endl;

	return 0;
}
