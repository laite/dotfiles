// Ex 16.38: class with nontype parameters

#include <iostream>
#include <string>

template <int he, int wi> class Screen
{
	public:

		Screen(): _height(he), _width(wi) { }

	private:

		int _width;
		int _height;
	};

int main()
{
	Screen<12, 40> myScreen();

	return 0;
}
