// Ex 7.34: multiple errors

#include "../Ch7Headers.h"
#include <cstdio> // for sprintf

const char *error(const char *c, int index, int upper_bound, char *buffer)
{
	sprintf(buffer,"%s (%d/%d)", c, index, upper_bound);

	return const_cast<const char*>(buffer);
}

const char *error(const char *c)
{
	return "asd";
}

string error(const char *c, char select_val)
{
	string s2(c);
	return s2 + select_val;
}

int main()
{
	int index = 5, upper_bound = 3;
	char selection = '>';
	char buffer[50];

	cout << error("Subscript out of bounds!", index, upper_bound, buffer) << endl;
	cout << error("Division!") << endl;
	cout << error("Invalid selection: ", selection) << endl;

	return 0;
}
