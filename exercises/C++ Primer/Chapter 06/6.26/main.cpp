// Ex 6.26: assert

#include "../Ch6headers.h"

int main()
{
	cout << "Whatever you do, don't type the word 'quit'" << endl;
	string s;
	while (cin >> s)
	{
		assert(s != "quit");
	}

	cout << "Thanks!" << endl;

	return 0;
}
