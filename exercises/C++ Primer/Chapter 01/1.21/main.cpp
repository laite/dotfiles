// Ex 1.

#include <iostream>
#include "../sales_item.h"

int main()
{
	Sales_item item;

	while (std::cin >> item)
	{
		std::cout << item << std::endl;
	}

	return 0;
}
