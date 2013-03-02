// Ex 18.26: pointers to class members

#include <iostream>
#include <string>

class Screen 
{
	public:

		Screen(): cursor(1), height(20), width(80) { }

		typedef std::string::size_type index;

		char get() const;
		char get(index ht, index wd) const;

		std::string contents;
		index cursor;
		index height;
		index width;
};

int main()
{
	Screen myScreen;
	Screen::index Screen::*ptr = &Screen::cursor;

	Screen::index local_cursor = myScreen.*ptr;

	std::cout << local_cursor << std::endl;

	return 0;
}
