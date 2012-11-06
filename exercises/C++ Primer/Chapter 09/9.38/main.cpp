// Ex 9.38: strings/find

#include "../../helpers.h"

const short kNumeric = 0, kAlphabetical = 1;

string names[] = { "numeric", "alphabetical" };
string types[] = { "0123456789", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };

int main()
{
	string s("ab2c3d7R4E6");

	for (short i = 0; i != 2; ++i)
	{
		string lookingFor(types[i]);
		string::size_type pos = 0;
		
		while ((pos = s.find_first_of(lookingFor, pos)) != string::npos)
		{
			cout << "There is " << names[i] << " character " << s[pos] << " at position " << pos << endl;
			++pos;
		}
	}

	// using s.find_first_not_of() in loop would be exactly same, but lookingFor would be reversed for types!

	return 0;
}
