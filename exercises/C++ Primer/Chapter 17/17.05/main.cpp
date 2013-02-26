// Ex 17.05: throwing stuff around

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

class exceptionObject { };
enum mathErr { overflow, underflow, zeroDivide };

typedef int EXCPTYPE;

int main()
{
	try {
		// these throw errors respectively to catch clauses below
		//
		// throw new exceptionObject();
		// throw overflow;
		// throw 24;
		// throw 24.0;
	}
	catch (exceptionObject *e)
	{
		std::cerr << "Error: exceptionObject*" << std::endl;
		abort();
	}
	catch (EXCPTYPE &i) // EXCPTYPE is just a glorified int
	{
		std::cerr << "error with EXCPTYPE" << std::endl;
		abort();
	}
	catch (mathErr &mathref)
	{
		std::cerr << "Math-error!" << std::endl;
		abort();
	}
	catch (...)
	{
		std::cerr << "Some other exception encountered!" << std::endl;
		throw; // Let's throw it away (to terminate)!
	}

	std::cout << "Graceful exit ahead." << std::endl;

	return 0;
}
