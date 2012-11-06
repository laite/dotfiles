// test for header files, multiple source files

#include <iostream>
#include "header.h"

int main()
{
	std::cout << HeaderFunction() << std::endl;
	std::cout << headerConst << "/" << headerData << std::endl;

	return 0;
}
