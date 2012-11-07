// Ex 11.07: two bad examples

#include "../../helpers.h"

int main()
{
	// example (a) - fixed version
	vector<int> vec;
	list<int> lst;
	int i;

	cout << "Please give some integers" << endl;

	while (cin >> i)
		lst.push_back(i);

	copy(lst.begin(), lst.end(), back_inserter(vec));

	PrintVector(vec);

	// example (b) - fixed version
	vector<int> iVec;
	iVec.resize(10); // set 10 empty items into vector
	fill_n(iVec.begin(), 10, 2);

	PrintVector(iVec);
	
	return 0;
}
