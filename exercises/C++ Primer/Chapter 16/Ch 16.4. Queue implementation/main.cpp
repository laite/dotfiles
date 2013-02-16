// Chapter 16.4. Queue implementation
// Requires C++11 (extended initializer list on vector)

#include <iostream>
#include <string>
#include <vector>

#include "queue.h"

int main()
{
	Queue<int> iQueue;
	Queue<int> userQ;
	Queue<std::string> userStringQ;

	for (int i=0; i != 10; ++i)
		iQueue.push(i);

	std::cout << iQueue << std::endl;

	// we can create Queue from different variable type through iterators
	std::vector<short> ssVec { 12, 13, 14, 19 };
	Queue<int> iQ2(ssVec.begin(), ssVec.end());

	short i[4] = { 1, 2, 1, 0 };
	iQueue.assign(i, i+4);

	std::cout << iQueue << std::endl;
	std::cout << iQ2 << std::endl;

	/*
		std::cout << "Your turn! Give me some integers [ctrl+d ends]" << std::endl;
		std::cin >> userQ;

		std::cin.clear();

		std::cout << "Nice! Now some strings" << std::endl;
		std::cin >> userStringQ;

		std::cout << userQ << std::endl;
		std::cout << userStringQ << std::endl;
	*/

	return 0;
}
