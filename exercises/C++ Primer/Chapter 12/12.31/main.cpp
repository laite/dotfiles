// Ex 12.31: pair initializing

#include "../../helpers.h"

struct Pair
{
	int x;
	int y;
};

int main()
{
	Pair p = { 0, 42 };

	// this won't compile, since pair<> must always be initialized through constructor
	pair<int, int> p2 = { 0, 42 };

	return 0;
}
