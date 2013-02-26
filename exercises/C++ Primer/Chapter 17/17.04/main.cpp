// Ex 17.04: error handling, 101

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

int main()
{
	try {
		throw std::runtime_error("test");
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		abort();
	}

	std::cout << "Graceful exit ahead." << std::endl;

	return 0;
}
