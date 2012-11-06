// Ex 9.25: erasing elements

#include "../../helpers.h"

int main()
{
	vector<int> iVec;
	int ex[10] = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
	PopulateIntVector(iVec, ex, ex + 10);
	PrintVector(iVec);

	iVec.erase(iVec.begin()+2, iVec.end());

	PrintVector(iVec);

	return 0;
}
