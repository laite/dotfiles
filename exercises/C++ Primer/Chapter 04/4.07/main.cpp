// Ex 4.07: copying arrays

#include "../Ch4headers.h"

int main()
{
	const size_t arraySize = 4;
	int ar1[] = { 2, 4, 6, 8 };
	int ar2[arraySize];
	vector<int> iVec1, iVec2;

	cout << "* Copying ar1 to ar2! *" << endl;

	for (size_t i = 0; i < arraySize; ++i)
		ar2[i] = ar1[i];

	cout << "Done! Printing out." << endl;

	for (size_t i = 0; i < arraySize; ++i)
		cout << ar1[i] << "/" << ar2[i] << endl;

	cout << "Trying to do the same with vectors..." << endl;

	for (int i=2; i < 9; i += 2)
		iVec1.push_back(i);

	// one can copy vectors through subscripts or iters
	for (vector<int>::size_type vs = 0; vs < iVec1.size(); ++vs)
		iVec2.push_back(iVec1[vs]);

	// for demonstration, we'll use iter to print 'em out
	for (vector<int>::const_iterator ci = iVec2.begin(); ci != iVec2.end(); ++ci)
		cout << "iVec2: " << *ci << endl;

	return 0;
}
