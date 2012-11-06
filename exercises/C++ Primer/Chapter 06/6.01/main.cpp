// Ex 6.1: null and not dull

#include "../Ch6headers.h"

int main()
{
	int a = 0;
	while (a++ != 512)
		; // null statement

	cout << "End is well." << endl;

	return 0;
}
