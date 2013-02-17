// Ex 16.52-16.54: template "count"

#include <iostream>
#include <string>
#include <vector>

template <typename T, typename U> unsigned int count_occurences_in_vector(const T& vec, const U& value)
{
	unsigned int hits = 0;

	for (typename T::const_iterator iter = vec.begin(); iter != vec.end(); ++iter)
		if (*iter == value)
			++hits;

	return hits;
}

// special version of count_occurences_in_vector to handle vectors of strings
template<> unsigned int count_occurences_in_vector<std::vector<std::string>, std::string>
(const std::vector<std::string> &vec, const std::string &value)
{
	unsigned int hits = 0;

	for (std::vector<std::string>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter)
	{
		// we make a substitute variable for clearing up the process
		std::string word = *iter;
		unsigned found = word.find(value);

		while (found != std::string::npos)
		{
			++hits;
			found=word.find(value,found+1);
		}
	}

	return hits;
}

int main()
{
	std::vector<int> iVec { 1, 2, 3, 3, 2, 3, 2, 1, 0 };
	std::vector<char> cVec { 'a', 'b', 'c', 'v', 'c', 'x' };
	std::vector<std::string> sVec { "this", "has", "my", "everything", "in", "winnings"};

	std::cout << count_occurences_in_vector(iVec, 3) << std::endl;
	std::cout << count_occurences_in_vector(cVec, 'c') << std::endl;
	std::cout << count_occurences_in_vector(sVec, std::string("in")) << std::endl;

	return 0;
}
