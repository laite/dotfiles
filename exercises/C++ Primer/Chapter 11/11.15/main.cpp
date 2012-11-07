// Ex 11.15: unique_copy

#include "../../helpers.h"

int main()
{
	vector<int> original, copyVector;
	PopulateIntVector(original, 30, 10);

	cout << "Original          : ";
	PrintVector(original);

	sort(original.begin(), original.end());
	unique_copy(original.begin(), original.end(), back_inserter(copyVector));
	
	cout << "Sorted original   : ";
	PrintVector(original);
	cout << "Unique copy       : ";
	PrintVector(copyVector);

	return 0;
}
