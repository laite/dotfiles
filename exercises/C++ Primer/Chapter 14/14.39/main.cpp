// Ex 14.39: Using library function objects
// C++11 required

// I couldn't figure out a simple way to compare string length with library function objects
// so this exercise is a bit wrong. It just compares equality on strings.
//
// Obviously, long solutions are found easily.

#include <iostream>
#include <string>
#include <algorithm>

const int kSearchValue(3);
const std::string kNewValue("*BURN*");

int main()
{
	std::vector<std::string> exampleStrings { "this", "has", "a", "lot", "of", "small", "strings" };
	
	replace_if(exampleStrings.begin(), exampleStrings.end(), std::bind2nd(std::equal_to<std::string>(), "has"), kNewValue);

	for (std::vector<std::string>::const_iterator iter = exampleStrings.begin();
			iter != exampleStrings.end(); ++iter)
		std::cout << *iter << " ";

	std::cout << std::endl;

	return 0;
}
