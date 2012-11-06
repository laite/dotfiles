// Ex 9.30: exploring the vector memory strategy

#include "../../helpers.h"

void PrintSizeAndCapacity(vector<int> &vector)
{
	cout << "size: " << vector.size()
		<< " capacity: " << vector.capacity() << endl;

	return;
}

int main()
{
	vector<int> iVec;
	PrintSizeAndCapacity(iVec);

	for (vector<int>::size_type i = 0; i != 20; ++i)
		iVec.push_back(0);

	PrintSizeAndCapacity(iVec);

	iVec.reserve(50);
	PrintSizeAndCapacity(iVec);

	for (vector<int>::size_type i = 0; i != 30; ++i)
		iVec.push_back(0);

	PrintSizeAndCapacity(iVec);
	iVec.push_back(42);
	PrintSizeAndCapacity(iVec);

	for (vector<int>::size_type i = 0; i != 50; ++i)
		iVec.push_back(0);

	PrintSizeAndCapacity(iVec);

	return 0;
}
