// Ex 11.17: pair of iterators

#include "../../helpers.h"

int main()
{
	istream_iterator<int> inputStart(cin);
	istream_iterator<int> inputEOF;

	cout << "Please give some integers!" << endl;

	// create vector from cin
	vector<int> intVector(inputStart, inputEOF);

	// printout
	PrintVector(intVector);

	return 0;
}
