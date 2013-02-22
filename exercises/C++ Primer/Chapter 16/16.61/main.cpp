// Ex 16.61: three versions of compare

#include <iostream>
#include <string>

template <class U, class V> int compare(U c1, U c2, V c3)
{
	std::cout << "compare <class U, class V> called! " << std::endl;
}

template <typename T> int compare(const T& c1, const T& c2)
{
	std::cout << "compare <typename T> called! " << std::endl;
}

int compare(const char *c1, const char *c2)
{
	std::cout << "ordinary compare called" << std::endl;
}

template <class T> T calc(T a, T b)
{
	std::cout << "<class T> calc" << std::endl;
}

template <> char calc(char a, char b)
{
	std::cout << "<char> calc" << std::endl;
}

double calc(double a, double b)
{
	std::cout << "calc(double)" << std::endl;
}

int main()
{
	const char const_arr1[] = "world", const_arr2[] = "hi";
	char ch_arr1[] = "world", ch_arr2[] = "hi";
	char *p1 = ch_arr1, *p2 = ch_arr2;

	// all these call <typename T> version of compare!
	compare(ch_arr1, const_arr1);
	compare(ch_arr2, const_arr2);
	compare(0,0);

	int ival = 1;
	double dval = 1.0;
	float fval = 0.4;

	calc(0, 'J'); // calls ordinary calc(double, double)!
	calc(0, ival); // calls <class T> template of calc (both parametres are int, no conversion needed)
	calc(0.25, dval); // calls ordinary calc(double, double)!
	calc(0, fval); // calls ordinary calc(double, double)!

	return 0;
}
