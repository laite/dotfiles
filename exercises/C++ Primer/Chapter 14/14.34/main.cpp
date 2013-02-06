// Ex 14.34: replacing values with function-object
// C++11 required

#include <iostream>
#include <string>
#include <algorithm>

const int kSearchValue(3);
const std::string kNewValue("*BURN*");

class EqualityClass {

	public:

		EqualityClass(int l): wantedLength(l) { }

		bool operator() (std::string);

	private:
		
		int wantedLength;
};

bool EqualityClass::operator() (std::string s)
{
	return (s.size() == wantedLength);
}

int main()
{
	std::vector<std::string> exampleStrings { "this", "has", "a", "lot", "of", "small", "strings" };

	EqualityClass wanted(kSearchValue);

	replace_if(exampleStrings.begin(), exampleStrings.end(), wanted, kNewValue);

	for (std::vector<std::string>::const_iterator iter = exampleStrings.begin();
			iter != exampleStrings.end(); ++iter)
		std::cout << *iter << " ";

	std::cout << std::endl;

	return 0;
}
