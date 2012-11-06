// Ex 9.12: two iterators, one int

#include "../Ch9Headers.h"

typedef vector<int>::const_iterator Iter;

bool FindValue(Iter begin, Iter end, int value)
{
	bool found = false;

	while (begin != end)
	{
		if (*begin == value)
			found = true;

		++begin;
	}

	return found;
}

int main()
{
	srand(time(0));
	vector<int> iVec;

	for (vector<int>::size_type is = 0; is != 20; ++is)
		iVec.push_back(rand()%20);

	if (FindValue(iVec.begin(), iVec.end(), 5))
		cout << "Value found!" << endl;
	else
		cout << "No luck this time." << endl;

	return 0;
}
