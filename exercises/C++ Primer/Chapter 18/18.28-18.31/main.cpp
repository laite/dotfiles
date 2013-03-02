// Ex 18.28: pointers to class members, inside class

#include <iostream>
#include <string>

class Screen 
{
	public:

		typedef Screen& (Screen::*movePointer)();

		//Screen(): cursor(1), height(20), width(80) { }
		Screen(movePointer m = &Screen::home): mPtr(m), cursor(1), height(20), width(80) { }

		typedef std::string::size_type index;

		char get() const { std::cout << "get()" << std::endl; }
		char get(index ht, index wd) const { std::cout << "get(index, index)" << std::endl; }

		void changeMovePointer(movePointer m) { mPtr = m; }

		Screen &home() { std::cout << "Going home." << std::endl; }
		Screen &end() { std::cout << "To the end." << std::endl; }
		std::string contents;
		index cursor;
		index height;
		index width;

		movePointer mPtr;
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

	(myScreen.*myScreen.mPtr)();

	myScreen.changeMovePointer(&Screen::end);
	(myScreen.*myScreen.mPtr)();

	return 0;
}
