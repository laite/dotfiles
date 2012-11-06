// Ex 6.11: loops while loops

#include "../Ch6headers.h"

int main()
{
	// (a): takes two words per loop from cin, couts them out
	string bufString, word;
	while (cin >> bufString >> word)
		cout << bufString << ", " << word << endl;

	// (b): since iter is destroyed and created with each loop, it'll never get to ivec.end() !
	// fix attempt:
	vector<int> ivec(4);
	vector<int>::iterator iter = ivec.begin();
	while (iter != ivec.end())
		++iter;

	// (c): fails looping immediately, since bool for ptr = 0 is always 0
	// fix attempt:
	int i; int *ptr = 0;
	while (ptr == 0)
		ptr = &i;

	// (d): silly loop, don't really understand what it's supposed to do?

	return 0;
}
