// Ex 17.14: namespaces and such

#include <iostream>
#include <string>
#include <stdexcept>

namespace Bookstore
{
	class out_of_stock: public std::runtime_error {

		public:

			explicit out_of_stock(const std::string &s): std::runtime_error(s) { }
	};

	class Sales_item 
	{
		public:
	
			Sales_item(const std::string &s): isbn(s) { }

			Sales_item operator+(const Sales_item&) throw (out_of_stock);
	
		private:
	
			std::string isbn;
	};

} // namespace Bookstore

// defining namespace function outside of namespace scope
// we 'dive' in Bookstore namespace after telling compiler our function is there
// so we can use unqualified member names in parametres, throw spec and in function body
Bookstore::Sales_item Bookstore::Sales_item::operator+(const Sales_item &rhs) throw (out_of_stock)
{
	// function body
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
