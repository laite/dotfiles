// Ex 16.15: telling the size of an array

#include <iostream>
#include <string>

template <typename T, std::size_t N> inline unsigned tell_size(T (&arr)[N])
{
	std::cout << N << std::endl;
}

int main()
{
	int x[33];
	std::string s[5];

	tell_size(x);
	tell_size(s);

	return 0;
}
