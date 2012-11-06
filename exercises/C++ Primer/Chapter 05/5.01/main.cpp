// Ex 5.01: Parentheses

#include "../Ch5headers.h"

int main()
{
	int result = 12 / 3 * 4 + 5 * 15 + 24 % 5 / 3;
	int pResult = ((12 /3) * 4) + (5 * 15) + (24 % 5 / 3);

	cout << result << " / " << pResult << endl;

	return 0;
}
