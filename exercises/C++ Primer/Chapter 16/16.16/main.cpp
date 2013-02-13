// Ex 16.16: out an array you shall

#include <iostream>
#include <string>

template <typename T, std::size_t N> inline unsigned print_array(T (&arr)[N])
{
	for (std::size_t i = 0; i < N; ++i)
		std::cout << arr[i] << " ";

	std::cout << std::endl;
}

int main()
{
	int x[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	std::string s[5] = { "a", "b", "c", "d", "e"};

	print_array(x);
	print_array(s);

	return 0;
}
