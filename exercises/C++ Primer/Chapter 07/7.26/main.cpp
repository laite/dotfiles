// Ex 7.26: plurals

#include "../Ch7Headers.h"

string &make_plural(string &s, char pluralSuffix = 's')
{
	s += pluralSuffix;
	return s;
}

int main()
{
	string success("success"), failure("failure");

	cout << "Plural of " << success << " is: " << make_plural(success, '\'') << endl;
	cout << "Plural of " << failure << " is: " << make_plural(failure) << endl;

	return 0;
}
