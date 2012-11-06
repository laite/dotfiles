// Ex 9.20: comparison of vector and list

#include "../../helpers.h"

bool AreContainersEqual(vector<int> &iVector, list<int> &iList)
{
	// Containers are equal if they have same number of equal elements
	if (iVector.size() != iList.size())
		return false;

	vector<int>::const_iterator vectorIter = iVector.begin();
	list<int>::const_iterator listIter = iList.begin();

	while (vectorIter != iVector.end())
	{
		if (*(vectorIter++) != *(listIter++))
			return false;
	}

	return true;
}

int main()
{
	vector<int> iVec;
	list<int> iList1, iList2;

	int numbers[7] = {1, 2, 3, 4, 7, 1, 8 };
	string equalityMessages[2] = { "Containers are NOT equal.", "Containers are equal." };

	iVec.insert(iVec.begin(), numbers, numbers+7);
	iList1.insert(iList1.begin(), numbers, numbers+7);
	iList2.insert(iList2.begin(), numbers+2, numbers+5);

	cout << equalityMessages[AreContainersEqual(iVec, iList1)] << endl;
	cout << equalityMessages[AreContainersEqual(iVec, iList2)] << endl;

	return 0;
}
