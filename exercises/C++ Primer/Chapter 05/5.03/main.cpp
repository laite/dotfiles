// Ex 5.03: even odds

#include "../Ch5headers.h"

int main()
{
	int i;

	cout << "Please give a number" << endl;
	cin >> i;

	if (i%2 != 0) {
		cout << i << " is an odd number" << endl;
	}
	else {
		cout << i << " is an even number" << endl;
	}

	return 0;
}
