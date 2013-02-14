// Ex 16.22

#include <iostream>
#include <string>

template <class Type> Type calc(const Type *array, int size)
{

}

template <class Type> Type fcn(Type p1, Type p2)
{
	
}

int main()
{
	double dobj;
	float fobj;
	char cobj;
	int ai[5] = { 511, 16, 8, 63, 34 };

	//calc(cobj, 'c'); // error! cobj can't be converted to Type *array
	calc(ai, 'c'); // ok! (char can be converted to int when it's not template argument)

	fcn(cobj, 'c'); // ok!

	//fcn(dobj, fobj); // error! double != float
	fcn(dobj, static_cast<double>(fobj)); // ok!

	std::cout << std::max<int>('a', 'e') << std::endl;

	return 0;
}
