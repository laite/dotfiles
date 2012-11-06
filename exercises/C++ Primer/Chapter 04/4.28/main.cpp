// Ex 4.28: vectors and arrays, dynamic memory allocating

#include "../Ch4headers.h"

int main()
{
	vector<int> myValues;

	int a;
	while (cin >> a) {
		myValues.push_back(a);
	}

	int *iva = new int[myValues.size()];
	int *ia = iva;

	for (size_t i = 0; i < myValues.size(); ++i) {
		*ia = myValues[i];
		++ia;
	}

	for (int *ib = iva; ib != (iva + myValues.size()); ++ib)
		cout << *ib << endl;

	delete [] iva; // in the end release

	return 0;
}
