// Ex 16.39: output operator to screen

#include <iostream>
#include <string>

// declare our templates
template <int wi, int he> class Screen;
template <int wi, int he> std::ostream& operator<<(std::ostream &os, const Screen<wi, he> &s);

// define class Screen
template <int wi, int he> class Screen
{
	// add operator<< as a friend for access to _width and _height
	friend std::ostream& operator<< <wi, he> (std::ostream&, const Screen<wi, he> &s);

	public:

		Screen(): _height(he), _width(wi) { }

	private:

		int _width;
		int _height;
};

template <int wi, int he> std::ostream& operator<<(std::ostream &os, const Screen<wi, he> &s)
{
	os << "screen is: " << s._width << "x" << s._height;

	return os;
}

int main()
{
	Screen<80, 22> myScreen;

	std::cout << myScreen << std::endl;

	return 0;
}
