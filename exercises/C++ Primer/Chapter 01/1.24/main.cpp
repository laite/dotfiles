// Ex 1.24 : several transactions

#include <iostream>
#include "../sales_item.h"

int main()
{
	Sales_item current, previous;

	std::cout << "Give items (ISBN amount price)" << std::endl;
	std::cin >> previous;
	std::cout << "Added " << previous << std::endl;

	while (std::cin >> current)
	{
		if (previous.same_isbn(current))
		{
			previous += current;
			std::cout << "Added " << current << std::endl;
		}
		else
		{
			std::cout << "Changing ISBN! Previous total: " << previous << std::endl;
			previous = current;
		}
	}

	std::cout << "Shutting down." << std::endl << "Previous total: " << previous << std::endl;

	return 0;
}
