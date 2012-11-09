// Ex 11.28: reverse_copy

#include "../../helpers.h"

int main()
{
	list<int> lst(50, 12);
	vector<int> vec1;
	
	list<int>::iterator it = lst.begin();
	for (list<int>::size_type i = 0; i != lst.size(); ++i)
		*it++ = rand()%(i+1);

	reverse_copy(lst.begin(), lst.end(), back_inserter(vec1));

	cout << "List:   " << flush;
	PrintList(lst);
	cout << "Vector: " << flush;
	PrintVector(vec1);

	list<int> l2;

	copy(lst.rbegin(), lst.rend(), front_inserter(l2));
	l2.sort();
	l2.unique();

	cout << "Unique: " << flush;
	PrintList(l2);

	return 0;
}
