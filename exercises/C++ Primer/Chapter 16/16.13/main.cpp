// Ex 16.13: printing contents

#include <iostream>
#include <string>
#include <vector>
#include <list>

template <typename T> void print_container(T &container)
{
	typename T::const_iterator iter = container.begin();

	// we use size_type as loop item instead of iterator
	// since exercise told us so :)
	for (typename T::size_type content = 0; content != container.size(); ++content)
		std::cout << *(iter++) << " ";

	std::cout << std::endl;
}

int main()
{
	std::vector<int> iVector { 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 3, 2, 1, 0 };
	std::list<int> iList(iVector.begin(), iVector.end());

	std::cout << "iVector: ";
	print_container(iVector);
	std::cout << "iList:   ";
	print_container(iList);

	return 0;
}
