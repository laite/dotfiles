// Ex 16.12: frequency findings

#include <iostream>
#include <string>
#include <vector>
#include <map>

template <typename T> typename T::value_type frequency(T begIter, T endIter)
{
	std::map<typename T::value_type, int> frequencies;
	typename std::map<typename T::value_type, int>::const_iterator freqIter;

	while (begIter != endIter)
	{
		frequencies[*begIter++]++;
	}

	int largest = 0;
	typename std::map<typename T::value_type, int>::const_iterator found = frequencies.end();

	for (freqIter = frequencies.begin(); freqIter != frequencies.end(); ++freqIter)
	{
		if (freqIter->second > largest)
		{
			largest = freqIter->second;
			found = freqIter;
		}
	}

	return found->first;
}

int main()
{
	std::vector<int> values { 1, 1, 1, 2, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 7, 2, 6 };

	int mostFrequent = frequency(values.begin(), values.end());

	std::cout << mostFrequent << std::endl;

	return 0;
}
