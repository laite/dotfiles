// Ex 9.34: uppercase string using iterator

#include "../../helpers.h"

int main()
{
	string s("This is still a string.");

	string::iterator sIter = s.begin();
	while (sIter != s.end())
		*sIter = toupper(*(sIter++));

	cout << s << endl;

	return 0;
}
