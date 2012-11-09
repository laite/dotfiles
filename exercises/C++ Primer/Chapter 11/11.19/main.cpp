// Ex 11.19: reverse iterators

#include "../../helpers.h"

int main()
{
	vector<int> iVec;

	for (vector<int>::size_type i = 0; i != 10; ++i)
		iVec.push_back(i);

	vector<int>::reverse_iterator reverseBegin = iVec.rbegin(), reverseEnd = iVec.rend();

	// print contents in reversed order
	while (reverseBegin != reverseEnd)
		cout << *reverseBegin++ << " ";

	cout << endl;

	return 0;
}
