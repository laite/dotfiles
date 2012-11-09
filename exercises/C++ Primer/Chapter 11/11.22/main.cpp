// Ex 11.22: copy reversed

#include "../../helpers.h"

int main()
{
	vector<int> iVec;
	list<int> iList;

	for (vector<int>::size_type i = 0; i != 10; ++i)
		iVec.push_back(i);

	cout << "vector: ";
	for (vector<int>::iterator vecIter = iVec.begin(); vecIter != iVec.end(); ++vecIter)
		cout << *vecIter << " ";

	cout << endl << "list:   ";

	// copy through places 7 to 3 (backwards) aka. values 6 5 4 3 2
	// note that we add +1 to end item, since we want one-past-end
	// also, note that rbegin() gives item number 10 (value 9)
	// aka: iVec.rbegin != iVec.end()
	copy(iVec.rbegin() + (10 - 7), iVec.rbegin() + (10 - 3) + 1, back_inserter(iList));

	for (list<int>::iterator i = iList.begin(); i != iList.end(); ++i)
		cout << *i << " ";

	cout << endl;

	return 0;
}
