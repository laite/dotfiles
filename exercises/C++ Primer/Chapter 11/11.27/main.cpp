// Ex 11.27: algorithms

#include "../../helpers.h"

bool isZero(const int &a)
{
	return a == 0;
}

int main()
{
	vector<int> source;

	for (vector<int>::size_type i = 0; i < 10; ++i)
		source.insert(source.begin(), i);

	replace(source.begin(), source.end(), 3, 30);
	replace_if(source.begin(), source.end(), isZero, 14);

	vector<int> destination;

	replace_copy(source.begin(), source.end(), back_inserter(destination), 4, 40);

	PrintVector(source);
	PrintVector(destination);


	return 0;
}
