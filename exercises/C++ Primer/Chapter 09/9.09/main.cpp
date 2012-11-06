// Ex 9.09: reversing lists

#include "../Ch9Headers.h"

const int kMaxListItems = 20, kMultiplier = 20;

int main()
{
	srand(time(0));

	list<int> iList;
	for (list<int>::size_type i = 0; i != kMaxListItems; ++i)
		iList.push_back(rand()%(1+i*kMultiplier));

	list<int>::const_iterator listIter = iList.end();

	while (listIter-- != iList.begin())
		cout << *listIter << ((listIter != iList.begin())? ", " : "\n");

	return 0;
}
