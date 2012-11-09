// Ex 11.21: find last item

#include "../../helpers.h"

int main()
{
	vector<int> iVec;
	PopulateIntVector(iVec, 20, 5);

	cout << "Items in vector:  " << flush;
	PrintVector(iVec, false, " ");

	vector<int>::reverse_iterator lastZero = find(iVec.rbegin(), iVec.rend(), 0);

	if (lastZero == iVec.rend())
	{
		cout << "No item 'zero' found" << endl;
		return -1;
	}

	vector<int>::iterator iter = iVec.begin();
	vector<int>::iterator regularIterLastZero = lastZero.base();

	cout << "Before last zero: " << flush;

	// we want to print items in 'right' order so we convert lastZero to regular iterator
	while (iter != (regularIterLastZero - 1))
		cout << *iter++ << " ";

	cout << endl;

	if (regularIterLastZero != iVec.end()) // if there really is a zero
	{
		cout << "After last zero:  " << flush;
		while (regularIterLastZero != iVec.end())
			cout << *regularIterLastZero++ << " ";
	}
	else
		cout << "There is no items after last zero!";

	cout << endl;

	return 0;
}
