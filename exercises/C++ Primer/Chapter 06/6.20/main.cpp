// Ex 6.20: twice is the charm

#include "../Ch6headers.h"

int main()
{
	string s, last("");
	while (cin >> s)
	{
		if (s == last)
			break;
		else
			last = s; 
	}

	if (s == last)
		cout << "Found a repeating word: " << last << endl;

	return 0;
}
