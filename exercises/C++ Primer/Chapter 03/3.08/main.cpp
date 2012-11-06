// Ex 3.08: Concatenating without a hint of a procrastination

#include <iostream>
#include <string>
#include "../Ch3headers.h"

int main()
{
	cout << "* Type some strings (Ctrl+d quits) *" << endl;

	string s(""), inputString;
	while (getline(cin,inputString))
		s += inputString;

	cout << s << endl;

	return 0;
}
