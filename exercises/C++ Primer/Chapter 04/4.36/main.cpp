// Ex 4.36: printing some multidimensional arrays

#include "../Ch4headers.h"

int main()
{
	int ia[3][4] = {
		{ 0, 1, 2, 3 },
		{ 4, 5, 6, 7 },
		{ 8, 9, 10, 11 }
	};

	int (*iPtr)[4] = ia;

	for (int (*p)[4] = iPtr; p != (iPtr + 3); ++p)
	{
		for (int *q = *p, *qe = *p + 4; q != qe; ++q)
			cout << *q << " ";
		cout << endl;
	}

	return 0;
}
