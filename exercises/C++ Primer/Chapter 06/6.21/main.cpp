// Ex 6.21: twice is the charm, as long as there's an uppercase

#include "../Ch6headers.h"

int main()
{
	cout << "Please give me words, and I'll tell if there's anything starting with an uppercase letter that duplicates" << endl;
	string s, last("");
	while (cin >> s)
	{
		if (!isupper(s[0]))
			continue;

		if (s == last)
			break;
		else
			last = s; 
	}

	if (s == last)
		cout << "Found a repeating word: " << last << endl;

	return 0;
}
