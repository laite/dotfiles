// Ex 17.13: namespaces

#include <iostream>
#include <string>
#include <stdexcept>

namespace Bookstore
{
	class out_of_stock: public std::runtime_error {

		public:

			explicit out_of_stock(const std::string &s): std::runtime_error(s) { }
	};
}

int main()
{
	try
	{
		throw Bookstore::out_of_stock("There is no such thing in the stock!");
	}
	catch (std::runtime_error e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
