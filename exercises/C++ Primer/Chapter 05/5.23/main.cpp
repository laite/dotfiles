// Ex 5.22: sizeof

#include "../Ch5headers.h"

int main()
{
	int x[10];
	int *p = x;

	cout << sizeof(x)/sizeof(*x) << endl; // 10
	cout << sizeof(p)/sizeof(*p) << endl; // 2
	// sizeof(*p) == sizeof(int) == sizeof(*x)

	int i = (*p = 5);

	return 0;
}
