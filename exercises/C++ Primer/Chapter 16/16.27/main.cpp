// Ex 16.27: Median function with template definition/declaration in own files
// Requires C++11

#include <iostream>
#include <string>
#include <vector>

#include "template.h"

int main()
{
	std::vector<int> iVec { 1, 2, 3, 40, 50, 60, 7, 8, 9 };
	std::vector<std::string> sVec { "a", "b", "c", "d" };

	std::cout << "median: " << *(median(sVec.begin(), sVec.end())) << std::endl;
	std::cout << "median: " << *(median(iVec.begin(), iVec.end())) << std::endl;

	return 0;
}
