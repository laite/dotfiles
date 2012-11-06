// Ex 4.33: copy vector of ints into an array

#include "../Ch4headers.h"

int main()
{
	vector<int> iVec;
	for (int i=0; i < 7; ++i)
		iVec.push_back(1 + rand()%39);

	int *arrayOfInts = new int[iVec.size()];
	cout << "Giving out free numbers!" << endl;

	for (int *iPtr = &arrayOfInts[0], i=0; iPtr != &arrayOfInts[0] + iVec.size(); ++iPtr, ++i)
	{
		*iPtr = iVec[i];
		cout << *iPtr << " ";
	}

	delete [] arrayOfInts;
	cout << endl;

	return 0;
}
