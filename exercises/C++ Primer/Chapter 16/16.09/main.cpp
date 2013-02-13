// Ex 16.09: templating the living shit out of find-algorithm

#include <iostream>
#include <string>
#include <vector>
#include <list>

template <typename T, typename U> T find_template(T begIter, T endIter, U &value)
{
	while (begIter != endIter)
	{
		if (*(begIter++) == value)
			return (--begIter);
	}

	return begIter;
}

int main()
{
	std::vector<int> iVec { 1, 2, 3, 4, 5, 6, 7, 8, 9, 45 };
	std::list<std::string> sVec { "these", "are", "some", "strings" };
	int wanted(45);
	std::string wanted2("hare");

	std::vector<int>::iterator found = find_template(iVec.begin(), iVec.end(), wanted);
	std::list<std::string>::iterator found2 = find_template(sVec.begin(), sVec.end(), wanted2);

	if (found != iVec.end())
		std::cout << "Found: " << *found << std::endl;
	else
		std::cout << wanted << " not found!" << std::endl;

	if (found2 != sVec.end())
		std::cout << "Found: " << *found2 << std::endl;
	else
		std::cout << wanted2 << " not found!" << std::endl;

	return 0;
}
