#include <algorithm>
#include <iostream>

// template median calculates median value of range and returns iterator to it
template <typename Iter> Iter median(Iter beginIter, Iter endIter)
{
	if (beginIter == endIter)
		return beginIter;

	std::sort(beginIter, endIter);

	return (beginIter+((endIter-beginIter)/2));
}
