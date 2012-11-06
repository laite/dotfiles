// Ex 4.18: ints to zeroes

#include "../Ch4headers.h"

int main()
{
	const size_t arraySize = 20;
	int array[arraySize];

	for (int *firstPointer = array, *lastPointer = array + arraySize;
		   	firstPointer != lastPointer; ++firstPointer)
		*firstPointer = 0;

	return 0;
}
