// Ex 18.27: pointers to class members

#include <iostream>
#include <string>

class Screen 
{
	public:

		Screen(): cursor(1), height(20), width(80) { }

		typedef std::string::size_type index;

		char get() const { std::cout << "get()" << std::endl; }
		char get(index ht, index wd) const { std::cout << "get(index, index)" << std::endl; }

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

	// method 1: we can typedef ourself a function pointer,
	// declare it to screen::get
	// and call it through myScreen instance
	typedef char (Screen::*get1)() const;
	get1 func = &Screen::get;
	(myScreen.*func)();

	// method 2: we can skip typedef altogether
	char (Screen::*get2)(Screen::index, Screen::index) const = &Screen::get;
	(myScreen.*get2)(11,22);

	return 0;
}
