// Ex 11.14: inserters

#include "../../helpers.h"

int main()
{
	vector<int> original;
	// put 20 random numbers (0-9) to original
	PopulateIntVector(original, 20, 10);

	// vector doesn't have push_front, so we have to use list for front_inserter
	list<int> frontList;
	vector<int> middleVector, endVector;

	replace_copy(original.begin(), original.end(), front_inserter(frontList), 0, 400);
	replace_copy(original.begin(), original.end(), inserter(middleVector, middleVector.begin()), 0, 400);
	replace_copy(original.begin(), original.end(), back_inserter(endVector), 0, 400);

	cout << "Original: ";
	PrintVector(original);
	// copy frontList to vector for printout
	vector<int> frontVector(frontList.begin(), frontList.end());
	cout << "Front   : ";
	PrintVector(frontVector);
	cout << "Middle  : ";
	PrintVector(middleVector);
	cout << "End     : ";
	PrintVector(endVector);

	return 0;
}
