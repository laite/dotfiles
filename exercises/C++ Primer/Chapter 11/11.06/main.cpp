// Ex 11.06: fill_n

#include "../../helpers.h"

int main()
{
	vector<int> iVec(13,13);

	// change 10 first items to 0
	fill_n(iVec.begin(), 10, 0);

	PrintVector(iVec);

	return 0;
}
