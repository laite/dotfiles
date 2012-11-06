// Ex 6.18: lexicographically less

#include "../Ch6headers.h"

int main()
{
	string s1, s2, userReaction;

	do
	{
		cout << "Please give two strings to compare." << endl;
		if (!(cin >> s1 >> s2))
			return -1;

		cout << "String \"" << ((s1 < s2)? s1 : s2) << "\" is smaller" << endl;

		cout << "Do you want to continue [yes/no]?" << endl;
		if (!(cin >> userReaction))
			userReaction = "no";

	} while (userReaction != "no");

	cout << "Ok, bye!" << endl;

	return 0;
}
