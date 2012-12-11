// Ex 12.22: fixing error in struct

#include "../../helpers.h"

struct X {
	int base;
	int rem;

	X (int i, int j): base(i), rem(i % j) { }
};

int main()
{
	
	return 0;
}
