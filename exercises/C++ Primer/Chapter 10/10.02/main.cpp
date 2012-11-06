// Ex 10.02: three little ways

#include "../../helpers.h"

int main()
{
	cout << "Please give a serie of strings and/or ints or anything." << endl;
	vector< pair<string, string> > pairVector;

	string firstString, lastString;
	pair< string, string > nextPair;

	while (cin >> firstString >> lastString)
	{
		// there are (according to c++ primer) at least three ways to initialize pair
		// i) nextPair = make_pair(firstString, lastString);
		// ii) pair< string, string> nextPair(firstString, lastString); // no definition before while() allowed
		// iii) nextPair = pair<string, string>(firstString, lastString);

		// let's use the last one here (even though it reminds of an old fashioned type cast)
		nextPair = pair<string, string>(firstString, lastString);
		pairVector.push_back(nextPair);
	}

	cout << "There are " << pairVector.size() << " elements in vector" << endl;

	return 0;
}
