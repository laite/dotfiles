// Ex 3.01: using namespaces

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	int base, exponent, result=1;

	cout << "Please give a base number and an exponent" << endl;
	cin >> base >> exponent;

	for (int i=1; i <= exponent; i++)
	{
		result = result*base;
		cout << base << "^" << i << " = " << result << endl;
	}

	return 0;
}
