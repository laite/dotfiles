// Ex 5.02: machine-dependency, and some

#include "../Ch5headers.h"

int main()
{
	int resultArray[] = { 
		-30 * 3 + 21 / 5,
		-30 + 3 * 21 / 5,
		30 / 3 * 21 % 5,
		-30 / 3 * 21 % 4,
		21 % -5, 21 / -5
	};

	int *rA = resultArray;

	for (int *rAEnd = rA + 6; rA!= rAEnd; ++rA)
		cout << *rA << endl;

	return 0;
}
