// Ex 9.36: initialize string from vector<char>

#include "../../helpers.h"

int main()
{
	vector<char> cVec;
	string s;

	// populate vector with some nonsense
	for (vector<char>::size_type i = 0; i != 10; ++i)
		cVec.push_back('a'+rand()%20);

	// move nonsense to string using iterators
	s.assign(cVec.begin(), cVec.end());

	// print out
	cout << s << endl;

	return 0;
}
