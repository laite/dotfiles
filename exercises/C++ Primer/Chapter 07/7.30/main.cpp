// Ex 7.30: inline functions

#include "../Ch7Headers.h"

inline string &get_shorter(string &s1, string &s2)
{
	return (s1.size() < s2.size()? s1 : s2);
}

int main()
{
	string s1("short"), s2("much longer!");

	get_shorter(s1, s2) = "Not so short anymore";

	cout << "s1: " << s1 << endl << "s2: " << s2 << endl;

	return 0;
}
