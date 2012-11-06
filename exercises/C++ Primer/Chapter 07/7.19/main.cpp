// Ex 7.19: references as function return value

#include "../Ch7Headers.h"

int &get(int *arry, int index)
{
	return arry[index];
}

int main()
{
	int ia[10];
	for (int i = 0; i != 10; ++i)
		get(ia, i) = 2;

	cout << get(ia, 3) << endl;

	return 0;
}
