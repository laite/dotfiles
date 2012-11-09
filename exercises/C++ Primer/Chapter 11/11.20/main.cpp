// Ex 11.19: iterators and reverse

#include "../../helpers.h"

int main()
{
	vector<int> iVec;

	for (vector<int>::size_type i = 0; i != 10; ++i)
		iVec.push_back(i);

	vector<int>::iterator iter = iVec.end();

	// print contents in reversed order [using regular iterator!]
	while (iter-- != iVec.begin())
		cout << *iter << " ";

	cout << endl;

	return 0;
}
