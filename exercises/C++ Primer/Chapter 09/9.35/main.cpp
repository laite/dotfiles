// Ex 9.35: erasing capital letters

#include "../../helpers.h"

int main()
{
	string s("This is StilL a StriNg.");

	string::iterator sIter = s.begin();
	while (sIter != s.end())
	{
		if (isupper(*sIter))
			sIter = s.erase(sIter);
		else
			++sIter;
	}

	cout << s << endl;

	return 0;
}
