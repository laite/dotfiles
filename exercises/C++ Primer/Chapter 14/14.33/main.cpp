// Ex 14.33: using function object with standard algorithms
// C++11 required

#include <iostream>
#include <string>
#include <algorithm>

const int kSearchValue = 5;

class GreaterThanClass {

	public:

		GreaterThanClass(int l): wantedLength(l) { }

		bool operator() (std::string);

	private:
		
		int wantedLength;
};

bool GreaterThanClass::operator() (std::string s)
{
	return s.size() >= wantedLength;
}

int main()
{
	std::vector<std::string> exampleStrings { "this", "has", "a", "lot", "of", "small", "strings" };

	GreaterThanClass greaterThanSearchValue(kSearchValue);

	std::vector<std::string>::iterator found = find_if(exampleStrings.begin(), exampleStrings.end(), greaterThanSearchValue);

	if (found != exampleStrings.end())
		std::cout << "Found word: " << *found << std::endl;
	else
		std::cout << "No match!" << std::endl;

	return 0;
}
