// Ex 12.30: vectors and constructors

#include "../../helpers.h"

void f(const vector<int> &iVecReference)
{
	return;
}

int main()
{
	vector<int> v2(42);
	F(v2);
	f(42); // this is an error; seems like the constructor for vector<int> is defined as *explicit*

	return 0;
}
