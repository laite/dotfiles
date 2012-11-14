// Ex 12.11: declaration/definition

#include "../../helpers.h"

// we tell that there's going to be struct called Y defined further
// this is sometimes referred to as "forward declaration"
// struct Y is 'incomplete' in sense that we have no idea of its properties
struct Y;

struct X
{
		// we can create pointer to declaration, but not object of struct Y
		// until Y is completely defined
		Y *yPointer;
};

struct Y
{
		// X is already defined above, so we can add items of type X
		X object;
};

int main()
{
	// X has only one property: pointer to Y
	X x;
	// Y has only one object X, which only points to some Y
	Y y;

	// we now have object x, which has reference to object y, which includes object x,
	// which has reference to y, which includes...
	y.object = x;
	x.yPointer = &y;

	return 0;
}
