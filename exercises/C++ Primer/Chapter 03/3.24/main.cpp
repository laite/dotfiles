// Ex 3.23: lighting some bits (fibonacci)

#include "../Ch3headers.h"

int main()
{
	bitset<32> myBit;

	int temp, i1 = 1, i2 = 2;
	while (i1 < 32)
	{
		myBit.set(i1-1);
		temp = i1+i2;
		i1 = i2;
		i2 = temp;
	}

	cout << myBit;

	return 0;
}
