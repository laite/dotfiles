// Ex 16.02: template functions
// C++11 required (auto)

#include <iostream>
#include <string>
#include <sstream>

template <typename T, typename U> bool write_to(T &os, U value)
{
	os << value;
	return static_cast<bool>(os);
}

int main()
{
	auto c("12000\n");
	std::stringstream ss;

	bool firstWrite = write_to(std::cout, c);

	// we can write "this", since our function doesn't expect reference
	bool secondWrite = write_to(ss, "this"); 

	std::cout << "bool values: " << firstWrite << ", " << secondWrite << std::endl;

	return 0;
}
