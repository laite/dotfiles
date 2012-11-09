// Ex 11.22: copy reversed

#include "../../helpers.h"

int main()
{
	vector<int> iVec;
	list<int> iList;

	for (vector<int>::size_type i = 1; i != 11; ++i)
		iVec.push_back(i);

	cout << "vector: ";
	for (vector<int>::iterator vecIter = iVec.begin(); vecIter != iVec.end(); ++vecIter)
		cout << *vecIter << " ";

	cout << endl << "list:   ";

	copy(iVec.rend() - 7, iVec.rend() - 2, back_inserter(iList));

	for (list<int>::iterator i = iList.begin(); i != iList.end(); ++i)
		cout << *i << " ";

	cout << endl;

	return 0;
}
