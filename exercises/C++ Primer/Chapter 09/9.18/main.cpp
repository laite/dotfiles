// Ex 9.18: elements from list of ints into two deques

#include "../../helpers.h"

int main()
{
	srand(time(NULL));

	list<int> source;
	deque<int> even, odd;

	// populate the source with random numbers [0,20)
	for (int i = 0; i != 20; ++i)
		source.push_back(rand()%20);

	list<int>::const_iterator listIterator = source.begin();

	// separate evens from odds
	while (listIterator != source.end())
	{
		if ((*listIterator)%2 == 0)
			even.push_back(*listIterator);
		else
			odd.insert(odd.begin(), *listIterator);

		++listIterator;
	}

	cout << "even: " << even.size() << endl << "odd: " << odd.size() << endl;

	return 0;
}
